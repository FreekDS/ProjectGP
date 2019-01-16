#include <GLL/Vehicle.h>
#include <iostream>

namespace RoadFighter {

    /**
     * Constructor for Vehicle.
     * @param speed Speed of the vehicle.
     */
    Vehicle::Vehicle(double speed)
            :m_speed(speed), m_movementSpeed(3.0), m_crashed(false), m_finished(false) { }

    /**
     * Getter for speed of vehicle.
     * @return Speed of vehicle.
     */
    double Vehicle::getSpeed() const
    {
        return m_speed;
    }

    /**
     * Setter for speed of vehicle.
     * @param speed New speed of vehicle.
     */
    void Vehicle::setSpeed(double speed)
    {
        Vehicle::m_speed = speed;
    }

    /**
     * Getter for the movement speed of the vehicle.
     * Divides movement speed by 1000 for appropriate movement speed in gll.
     * @param division Divider of movement speed, default 1000.
     * @return Movement speed of the vehicle.
     */
    double Vehicle::getMovespeed(double division) const
    {
        return m_movementSpeed / division;
    }

    /**
     * Setter for the movement speed of the vehicle.
     * @param ms Movement speed of the vehicle.
     */
    void Vehicle::setMoveSpeed(double ms)
    {
        m_movementSpeed = ms;
    }

    /**
     * Default constructor for vehicle.
     */
    Vehicle::Vehicle() : m_speed(0), m_movementSpeed(3.0), m_crashed(false), m_repairTime(1000), m_finished(false)
    {
        setType(EntityType::VEHICLE);
    }

    /**
     * Determine whether the vehicle is significantly moving (~speed > 0.3).
     * @return True when Vehicle moves.
     */
    bool Vehicle::isMoving() const
    {
        return m_speed > 0.3;
    }

    /**
     * This function lets a vehicle crash. (sets its variable to true).
     */
    void Vehicle::crash()
    {
        m_crashed = true;
    }

    /**
     * Determine whether the vehicle has crashed or not.
     * @return True if the vehicle has crashed, else false.
     */
    bool Vehicle::hasCrashed() const
    {
        return m_crashed;
    }

    /**
     * Repairs the car.
     * Sets crashed to false.
     */
    bool Vehicle::repair(bool immediate)
    {
        if(immediate){
            m_crashed = false;
            return true;
        }
        if(m_repairTimer.timerRunning()){
            if (m_repairTimer.timerFinished()) {
                m_repairTimer.reset();
                m_crashed = false;
                return true;
            }
        }else {
            m_repairTimer.setTimer(m_repairTime);
            m_repairTimer.startTimer();
        }
        return false;
    }

    /**
     * Sets the time it takes to repair the vehicle.
     * @param repairTime Time it takes to repair in milliseconds.
     */
    void Vehicle::setRepairTime(int repairTime)
    {
        m_repairTime = repairTime;
        m_repairTimer.setTimer(repairTime);
    }

    bool Vehicle::hasFinished() const
    {
        return m_finished;
    }

    void Vehicle::finish()
    {
        m_finished = true;
    }

} // namespace RoadFighter
