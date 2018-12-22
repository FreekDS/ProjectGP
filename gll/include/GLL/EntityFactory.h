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
         * Pure virtual function which will create a Player
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createPlayer() const = 0;

        /**
         * Pure virtual function which will create a Bullet
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createBullet() const = 0;

        /**
         * Pure virtual function which will create a Passing Car
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createPassingCar(shared_ptr<World> world, shared_ptr<Player> player) const = 0;

        /**
         * Pure virtual function which will create a Race Car
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createRaceCar() const = 0;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ABSTRACTFACTORY_H
