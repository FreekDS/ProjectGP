#ifndef ROADFIGHTER_ABSTRACTFACTORY_H
#define ROADFIGHTER_ABSTRACTFACTORY_H

#include "Entity.h"
#include "Player.h"
#include <memory>

using namespace std;

namespace RoadFighter {

    class World;

    /**
     * This class is used to create all entities
     * This class is based on the Abstract Factory design pattern
     */
    class EntityFactory {
    public:
        /**
         * Pure virtual function which will create a Player.
         * @return shared pointer to an Entity.
         */
        virtual shared_ptr<Entity> createPlayer() const = 0;

        /**
         * Pure virtual function which will create a Bullet.
         * @param world shared pointer to world.
         * @param player shared pointer to player.
         * @return shared pointer to an Entity.
         */
        virtual shared_ptr<Entity> createBullet(const RoadFighter::Position& playerPos, double playerHeight) const = 0;

        /**
         * Pure virtual function which will create a Passing Car
         * @param world shared pointer to world.
         * @param player shared pointer to player.
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createPassingCar(shared_ptr<World> world, shared_ptr<Player> player) const = 0;

        /**
         * Pure virtual function which will create a Race Car
         * @param world shared pointer to world.
         * @param player shared pointer to player.
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createRaceCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const = 0;

        /**
         * This function creates a finishLine.
         * @param world Shared pointer to the world.
         * @return Shared pointer to the finish line.
         */
        shared_ptr<Entity> createFinishLine(const shared_ptr<World>& world) const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ABSTRACTFACTORY_H
