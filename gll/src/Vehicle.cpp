#include <GLL/Vehicle.h>


namespace RoadFighter {

    /**
     * Constructor for Vehicle
     * @param speed Speed of the vehicle
     */
    Vehicle::Vehicle(double speed)
            :m_speed(speed), m_movementSpeed(0.001) { }

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

    double Vehicle::getMovespeed() const
    {
        return m_movementSpeed;
    }

    void Vehicle::setMovespeed(double ms)
    {
        m_movementSpeed = ms;
    }

    /**
     * Default constructor for vehicle
     */
    Vehicle::Vehicle() : m_speed(0), m_movementSpeed(0.01) {}

} // namespace RoadFighter
