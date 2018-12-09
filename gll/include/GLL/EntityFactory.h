#ifndef ROADFIGHTER_ABSTRACTFACTORY_H
#define ROADFIGHTER_ABSTRACTFACTORY_H

#include "Entity.h"
#include <memory>

using namespace std;

namespace RoadFighter {

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
        virtual shared_ptr<Entity> createPassingCar() const = 0;

        /**
         * Pure virtual function which will create a Race Car
         * @return shared pointer to an Entity
         */
        virtual shared_ptr<Entity> createRaceCar() const = 0;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ABSTRACTFACTORY_H
