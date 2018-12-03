#include "GLL/Vehicle.h"

namespace RoadFighter {

    Vehicle::Vehicle(double speed)
            :m_speed(speed) { }

    double Vehicle::getSpeed() const
    {
        return m_speed;
    }

    void Vehicle::setSpeed(double speed)
    {
        Vehicle::m_speed = speed;
    }

    Vehicle::Vehicle() = default;

} // namespace RoadFighter
