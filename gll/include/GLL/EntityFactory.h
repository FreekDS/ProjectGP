#ifndef ROADFIGHTER_ABSTRACTFACTORY_H
#define ROADFIGHTER_ABSTRACTFACTORY_H

#include "Entity.h"
#include <memory>

using namespace std;

namespace RoadFighter {

    class EntityFactory {
    public:
        virtual shared_ptr<Entity> createPlayer() const = 0;
        virtual shared_ptr<Entity> createBullet() const = 0;
        virtual shared_ptr<Entity> createPassingCar() const = 0;
        virtual shared_ptr<Entity> createRaceCar() const = 0;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ABSTRACTFACTORY_H
