#ifndef ROADFIGHTER_WORLD_H
#define ROADFIGHTER_WORLD_H

#include "Entity.h"
#include "EntityFactory.h"
#include "Player.h"
#include <vector>
#include <memory>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents the World of Road Fighter
     * Based on Composite design pattern
     */
    class World : public Entity {
    protected:
        vector<shared_ptr<Entity>> m_childEntities;
        shared_ptr<EntityFactory> m_factory;
    public:
        /**
         * Default constructor of World
         */
        World();

        /**
         * Setter for the Entity factory of the world
         * @param factory EntityFactory of the world
         */
        void setFactory(const shared_ptr<EntityFactory>& factory);

        /**
         * Getter for the EntityFactory of the world
         * @return Reference to the EntityFactory
         */
        const shared_ptr<EntityFactory>& getFactory() const;

        /**
         * Default destructor of World
         */
        ~World() override;

        /**
         * Assignment operator for World
         * @param other World to assign this one to
         * @return Reference to a World object
         */
        World& operator=(const World& other);

        /**
         * Adds an Entity to the world
         * Part of the Composite design pattern
         * @param entity
         */
        void add(shared_ptr<Entity> entity);

        /**
         * Remove an Entity of the world
         * Part of the Composite design pattern
         * @param entity Entity which needs to be removed
         */
        void remove(shared_ptr<Entity> entity);

        /**
         * Check whether the world is empty or not
         * @return True if the world has no Entities in it
         */
        bool empty();

        /**
         * Check for collision between two entities
         * @param entity1 First Entity to check
         * @param entity2 Second Entity to check
         * @return True if entity1 and entity2 collide
         */
        bool checkCollision(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2);

        /**
         * Determine whether the Entity can be destroyed or not
         * @return False, the world cannot be destroyed during the game
         */
        bool canBeDestroyed() const override;

        /**
         * Searches for the player in the child entities and returns it if found
         * @return Shared pointer of an entity (= the player), if nothing found, nullptr
         */
        shared_ptr<Entity> getPlayer() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_WORLD_H
