#include <GLL/World.h>
#include <GLL/Random.h>
#include <algorithm>
#include <iostream>

namespace RoadFighter {

    /**
     * Adds an Entity to the world.
     * Part of the Composite design pattern.
     * @param entity Entity to add.
     */
    void World::add(shared_ptr<Entity> entity)
    {
        m_childEntities.emplace_back(entity);
    }

    /**
     * Remove an Entity of the world.
     * Part of the Composite design pattern.
     * @param entity Entity which needs to be removed.
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
     * Check whether the world is empty or not.
     * @return True if the world has no Entities in it.
     */
    bool World::empty()
    {
        return m_childEntities.empty();
    }

    /**
     * Check for collision between two entities.
     * @param entity1 First Entity to check.
     * @param entity2 Second Entity to check.
     * @return True if entity1 and entity2 collide.
     */
    bool World::checkCollision(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2) const
    {
        auto doOverlap = [](const BoxCollider& c1, const BoxCollider& c2) -> bool {
            if (c1.getUpperLeftCorner().x>=c2.getBottomRightCorner().x
                    || c2.getUpperLeftCorner().x>=c1.getBottomRightCorner().x)
                return false;
            return !(c1.getUpperLeftCorner().y<=c2.getBottomRightCorner().y
                    || c2.getUpperLeftCorner().y<=c1.getBottomRightCorner().y);
        };

        for (const BoxCollider& collider1 : entity1->getColliders()) {
            for (const BoxCollider& collider2 : entity2->getColliders()) {
                if (!collider1.isEnabled() || !collider2.isEnabled())
                    continue;
                if (doOverlap(collider1, collider2)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Assignment operator for World.
     * @param other World to assign this one to.
     * @return Reference to a World object.
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
     * Default destructor of World.
     */
    World::~World() = default;

    /**
     * Default constructor of World.
     */
    World::World()
            :m_factory(nullptr), m_boundary1(-0.7), m_boundary2(1.3), m_neededDistanceCovered(false),
             m_finishSpriteLoaded(false), m_stopLoop(false), m_distanceToCover(1200)
    {
        setType(EntityType::WORLD);
        setUpperLeftCorner({-4, 3});
        setBottomRightCorner({4, -3});
        resetSpawnTimer();
        m_spawnCooldown.startTimer();
    }

    /**
    * Getter for the EntityFactory of the world.
    * @return Reference to the EntityFactory.
    */
    const shared_ptr<EntityFactory>& World::getFactory() const
    {
        return m_factory;
    }

    /**
     * Setter for the Entity factory of the world.
     * @param factory EntityFactory of the world.
     */
    void World::setFactory(const shared_ptr<EntityFactory>& factory)
    {
        World::m_factory = factory;
    }

    /**
     * Determine whether the Entity can be destroyed or not.
     * @return False, the world cannot be destroyed during the game.
     */
    bool World::canBeDestroyed() const
    {
        return false;
    }

    /**
     * Searches for the player in the child entities and returns it if found.
     * @return Shared pointer of an entity (= the player), if nothing found, nullptr.
     */
    shared_ptr<Entity> World::getPlayer() const
    {
        for (const auto& entity : m_childEntities) {
            if (entity->getType()==EntityType::PLAYER)
                return entity;
        }
        return nullptr;
    }

    /**
     * Getter for boundary1 of world.
     * @return Boundary1.
     */
    double World::getLeftBoundary() const
    {
        return m_boundary1;
    }

    /**
     * Getter for boundary2 of world.
     * @return Boundary2.
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
                        if (entity2->getType()==FINISH) {
                            vehicle->finish();
                            continue;
                        }
                        if (vehicle->hasCrashed())
                            continue;
                        vehicle->crash();
                    }
                    if (dynamic_pointer_cast<RoadFighter::Vehicle>(entity2)) {
                        auto vehicle = dynamic_pointer_cast<RoadFighter::Vehicle>(entity2);
                        if (entity1->getType()==FINISH) {
                            vehicle->finish();
                            continue;
                        }
                        if (vehicle->hasCrashed())
                            continue;
                        vehicle->crash();
                    }

                }
            }
    }

    /**
     * Updates the world and all its components.
     * - if the game has finished, this function does nothing
     * - collision will be checked @see checkCollisionOfAll()
     * - will check if the distance that needs to be covered has been covered
     * - removes entities that are allowed to be removed @see removeRemovableEntities()
     * - spawns new entities if the spawn timer has finished
     * - calls all update function of the child entities
     * - reads the input of the user using @see readInput()
     */
    void World::update()
    {
        if (gameFinished())
            return;

        // check for collision
        checkCollisionOfAll();

        if (dynamic_pointer_cast<Player>(getPlayer())->getCoveredDistance()>=m_distanceToCover) {
            m_neededDistanceCovered = true;
        }

        // remove entities
        removeRemovableEntities();

        // add new entities
        if (m_spawnCooldown.timerFinished()) {
            add(m_factory->createPassingCar(getPtr(), dynamic_pointer_cast<Player>(getPlayer())));
            resetSpawnTimer();
        }

        // update entities
        for (const auto& entity : m_childEntities) {
            entity->update();
        }
        readInput();
    }

    /**
     * Sets the racing cars.
     */
    void World::setupRaceCars()
    {
        if (getPlayer()==nullptr)
            throw std::invalid_argument("Add a player to the world before adding race cars");
        for (int i = 0; i<5; i++) {
            shared_ptr<World> world = getPtr();
            shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
            add(m_factory->createRaceCar(world, player));
        }
    }

    /**
     * Getter for the entities of the world.
     * @return Vector of shared pointers to the entities.
     */
    const vector<shared_ptr<Entity>>& World::getEntities()
    {
        return m_childEntities;
    }

    /**
     * This function checks if the needed distance is covered.
     * @return True if the needed distance is covered.
     */
    bool World::neededDistanceCovered() const
    {
        return m_neededDistanceCovered;
    }

    /**
     * This function checks if the finishline sprite is covered.
     * @return True if the finish line sprite is loaded.
     */
    bool World::finishSpriteLoaded() const
    {
        return m_finishSpriteLoaded;
    }

    /**
     * Creates a finish line.
     */
    void World::spawnFinishline()
    {
        add(m_factory->createFinishLine(getPtr()));
    }

    /**
     * Returns true if the player finished the game.
     * @return True if the player has finished the game.
     */
    bool World::gameFinished() const
    {
        shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
        return player->hasFinished();
    }

    /**
     * Returns the score of the player.
     * @return Score of the player
     */
    unsigned int World::getScore() const
    {
        shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
        shared_ptr<ScoreObserver> scoreObserver;
        for (auto& obs : player->getObservers()) {
            if (obs->getType()==ObserverType::SCORE) {
                scoreObserver = dynamic_pointer_cast<ScoreObserver>(obs);
                break;
            }
        }
        return scoreObserver->getScore();
    }

    /**
     * Calculates the amount of race cars behind the player.
     * @return The number of race cars behind the player.
     */
    unsigned int World::getRaceCarsBehindPlayer() const
    {
        shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
        unsigned int counter = 0;
        for (auto& entity : m_childEntities) {
            if (entity->getType()!=EntityType::RACE_CAR)
                continue;
            if (entity->getPos().y<player->getPos().y-0.01)
                counter++;
        }
        return counter;
    }

} // namespace RoadFighter
