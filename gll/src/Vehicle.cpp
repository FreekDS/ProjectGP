#include "GLL/Vehicle.h"

namespace RoadFighter {

    /**
     * Constructor for Vehicle
     * @param speed Speed of the vehicle
     */
    Vehicle::Vehicle(double speed)
            :m_speed(speed) { }

    /**
     * Getter for speed of vehicle
     * @return Speed of vehicle
     */
    double Vehicle::getSpeed() const
    {
        return m_speed;
    }

    /**
     * Setter for speed of vehicle
     * @param speed New speed of vehicle
     */
    void Vehicle::setSpeed(double speed)
    {
        Vehicle::m_speed = speed;
    }

    /**
     * Default constructor for vehicle
     */
    Vehicle::Vehicle() = default;

} // namespace RoadFighter
