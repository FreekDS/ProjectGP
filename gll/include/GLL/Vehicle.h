#ifndef ROADFIGHTER_VEHICLE_H
#define ROADFIGHTER_VEHICLE_H

#include "Entity.h"

namespace RoadFighter {

    class Vehicle : public Entity {
    private:
        double m_speed;
    public:
        Vehicle();

        explicit Vehicle(double speed);

        double getSpeed() const;

        void setSpeed(double speed);

        virtual void accelerate() = 0;

        virtual void moveLeft() = 0;

        virtual void moveRight() = 0;

        virtual void moveUp() = 0;

        virtual void moveDown() = 0;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_VEHICLE_H
