#include <GLL/World.h>
#include <GLL/Random.h>
#include <algorithm>
#include <iostream>

namespace RoadFighter {

    /**
     * Adds an Entity to the world
     * Part of the Composite design pattern
     * @param entity
     */
    void World::add(shared_ptr<Entity> entity)
    {
        m_childEntities.emplace_back(entity);
    }

    /**
     * Remove an Entity of the world
     * Part of the Composite design pattern
     * @param entity Entity which needs to be removed
     */
    void World::remove(shared_ptr<Entity> entity)
    {
        for (unsigned int i = 0; i<m_childEntities.size(); i++) {
            if (entity==m_childEntities[i]) {
                m_childEntities.erase(m_childEntities.begin()+i);
                break;
            }
        }
    }

    /**
     * Check whether the world is empty or not
     * @return True if the world has no Entities in it
     */
    bool World::empty()
    {
        return m_childEntities.empty();
    }

    /**
     * Check for collision between two entities
     * @param entity1 First Entity to check
     * @param entity2 Second Entity to check
     * @return True if entity1 and entity2 collide
     */
    bool World::checkCollision(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2) const
    {
        auto doOverlap = [](const BoxCollider& c1, const BoxCollider& c2) -> bool {
            if (c1.getUpperLeftCorner().x>c2.getBottomRightCorner().x
                    || c2.getUpperLeftCorner().x>c1.getBottomRightCorner().x)
                return false;
            return !(c1.getUpperLeftCorner().y<c2.getBottomRightCorner().y
                    || c2.getUpperLeftCorner().y<c1.getBottomRightCorner().y);
        };

        for (const BoxCollider& collider1 : entity1->getColliders()) {
            for (const BoxCollider& collider2 : entity2->getColliders()) {
                if (doOverlap(collider1, collider2)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Assignment operator for World
     * @param other World to assign this one to
     * @return Reference to a World object
     */
    World& World::operator=(const World& other)
    {
        if (this==&other)
            return *this;
        m_childEntities = other.m_childEntities;
        m_factory = other.m_factory;
        return *this;
    }

    /**
     * Default destructor of World
     */
    World::~World() = default;

    /**
     * Default constructor of World
     */
    World::World()
            :m_factory(nullptr), m_boundary1(-0.56), m_boundary2(1.17)
    {
        setUpperLeftCorner({-4, 3});
        setBottomRightCorner({3, -4});
        resetSpawnTimer();
        m_spawnCooldown.startTimer();
    }

    /**
    * Getter for the EntityFactory of the world
    * @return Reference to the EntityFactory
    */
    const shared_ptr<EntityFactory>& World::getFactory() const
    {
        return m_factory;
    }

    /**
     * Setter for the Entity factory of the world
     * @param factory EntityFactory of the world
     */
    void World::setFactory(const shared_ptr<EntityFactory>& factory)
    {
        World::m_factory = factory;
    }

    /**
     * Determine whether the Entity can be destroyed or not
     * @return False, the world cannot be destroyed during the game
     */
    bool World::canBeDestroyed() const
    {
        return false;
    }

    /**
     * Searches for the player in the child entities and returns it if found
     * @return Shared pointer of an entity (= the player), if nothing found, nullptr
     */
    shared_ptr<Entity> World::getPlayer() const
    {
        for (const auto& entity : m_childEntities) {
            if (entity->isPlayer())
                return entity;
        }
        return nullptr;
    }

    /**
     * Getter for boundary1 of world
     * @return Boundary1
     */
    double World::getLeftBoundary() const
    {
        return m_boundary1;
    }

    /**
     * Getter for boundary2 of world
     * @return Boundary2;
     */
    double World::getRightBoundary() const
    {
        return m_boundary2;
    }

    /**
     * Returns a shared pointer of this World.
     * @return Shared pointer of this world.
     */
    shared_ptr<World> World::getPtr()
    {
        return shared_from_this();
    }

    /**
     * Removes all entities that can be removed from the list.
     */
    void World::removeRemovableEntities()
    {
        auto erase = [](shared_ptr<Entity> entity) { return entity->canBeDestroyed(); };
        m_childEntities.erase(std::remove_if(m_childEntities.begin(), m_childEntities.end(), erase),
                m_childEntities.end());
    }

    /**
     * Resets the spawn timer.
     */
    void World::resetSpawnTimer()
    {
        auto random = Random::getInstance();
        m_spawnCooldown.setTimer(random->randInt(100, 3000));
    }

    /**
     * Checks all entities for collision.
     */
    void World::checkCollisionOfAll() const
    {
        for (const auto& entity1 : m_childEntities)
            for (const auto& entity2 : m_childEntities) {
                if (entity1==entity2)
                    continue;
                if (checkCollision(entity1, entity2)) {
                    if (dynamic_pointer_cast<RoadFighter::Vehicle>(entity1)) {
                        auto vehicle = dynamic_pointer_cast<RoadFighter::Vehicle>(entity1);
                        if (vehicle->hasCrashed())
                            continue;
                        vehicle->crash();
                    }
                    if (dynamic_pointer_cast<RoadFighter::Vehicle>(entity2)) {
                        auto vehicle = dynamic_pointer_cast<RoadFighter::Vehicle>(entity2);
                        if (vehicle->hasCrashed())
                            continue;
                        vehicle->crash();
                    }

                }
            }
    }

    /**
     * Updates the world and all its components
     * This function first updates all the components
     * After that it will read the input with @see readInput()
     */
    void World::update()
    {
        // check for collision
        checkCollisionOfAll();

        // remove entities
        removeRemovableEntities();

        // add new entities
        if (m_spawnCooldown.timerFinished()) {
            if (m_childEntities.size()>10) {
//                cout << "Exceeded max entities! " << m_childEntities.size() <<endl;
            }
            else {
                add(m_factory->createPassingCar(getPtr(), dynamic_pointer_cast<Player>(getPlayer())));
                resetSpawnTimer();
            }
        }

        // update entities
        for (const auto& entity : m_childEntities) {
            entity->update();
        }
        readInput();
    }

} // namespace RoadFighter
