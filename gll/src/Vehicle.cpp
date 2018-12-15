#include <GLL/Vehicle.h>


namespace RoadFighter {

    /**
     * Constructor for Vehicle
     * @param speed Speed of the vehicle
     */
    Vehicle::Vehicle(double speed)
            :m_speed(speed), m_movementSpeed(3.0) { }

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
     * Getter for the movement speed of the vehicle
     * Divides movement speed by 1000 for appropriate movement speed in gll
     * @param division Divider of movement speed, default 1000
     * @return Movement speed of the vehicle
     */
    double Vehicle::getMovespeed(double division) const
    {
        return m_movementSpeed / division;
    }

    /**
     * Setter for the movement speed of the vehicle
     * @param ms Movement speed of the vehicle
     */
    void Vehicle::setMoveSpeed(double ms)
    {
        m_movementSpeed = ms;
    }

    /**
     * Default constructor for vehicle
     */
    Vehicle::Vehicle() : m_speed(0), m_movementSpeed(3.0) {}

    /**
     * Determine whether the vehicle is significantly moving (~speed > 0.3)
     * @return True when Vehicle moves
     */
    bool Vehicle::isMoving() const
    {
        return m_speed > 0.3;
    }

} // namespace RoadFighter
