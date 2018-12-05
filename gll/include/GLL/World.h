#ifndef ROADFIGHTER_WORLD_H
#define ROADFIGHTER_WORLD_H

#include "Entity.h"
#include <vector>
#include <memory>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents the World of Road Fighter
     * Based on Composite design pattern
     */
    class World : public Entity {
    private:
        vector<shared_ptr<Entity>> m_childEntities;
    public:
        /**
         * Default constructor of World
         */
        World();

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
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_WORLD_H
