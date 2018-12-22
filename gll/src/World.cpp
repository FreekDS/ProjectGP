#include <GLL/World.h>

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
    bool World::checkCollision(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2)
    {
        // todo implement
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


} // namespace RoadFighter
