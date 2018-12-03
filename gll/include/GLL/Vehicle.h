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
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_VEHICLE_H
