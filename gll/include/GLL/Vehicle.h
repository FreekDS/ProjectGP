#ifndef ROADFIGHTER_VEHICLE_H
#define ROADFIGHTER_VEHICLE_H

#include "Entity.h"

namespace RoadFighter {

    /**
     * This is an abstract class which represents a Vehicle
     * This class is derived from @see Entity
     * A vehicle has:
     * - a driving speed
     * - a movement speed (for horizontal and vertical movement in the grid)
     */
    class Vehicle : public Entity {
    private:
        double m_speed;
        double m_movementSpeed;
    public:
        /**
         * Default constructor for vehicle
         */
        Vehicle();

        /**
         * Constructor for Vehicle
         * @param speed Speed of the vehicle
         */
        explicit Vehicle(double speed);

        /**
         * Getter for speed of vehicle
         * @return Speed of vehicle
         */
        double getSpeed() const;

        /**
         * Setter for speed of vehicle
         * @param speed New speed of vehicle
         */
        void setSpeed(double speed);

        /**
         * Pure virtual function to accelerate the vehicle
         */
        virtual void accelerate() = 0;

        /**
         * Pure virtual function to slow down the player
         */
        virtual void slowDown() = 0;

        /**
         * Pure virtual function to move the vehicle to the left
         * @param world_boundary Left boundary of the world
         */
        virtual void moveLeft(double world_boundary) = 0;

        /**
         * Pure virtual function to move the vehicle to the right
         * @param world_boundary Right boundary of the world
         */
        virtual void moveRight(double world_boundary) = 0;

        /**
         * Pure virtual function to move the vehicle up
         */
        virtual void moveUp() = 0;

        /**
         * Pure virtual function to move the vehicle down
         */
        virtual void moveDown() = 0;

        /**
         * Getter for the movement speed of the vehicle
         * Divides movement speed by 1000 for appropriate movement speed in gll
         * @param division Divider of movement speed, default 1000
         * @return Movement speed of the vehicle
         */
        double getMovespeed(double division = 140) const;

        /**
         * Setter for the movement speed of the vehicle
         * @param ms Movement speed of the vehicle
         */
        void setMoveSpeed(double ms);

        /**
         * Determine whether the vehicle is significantly moving (~speed > 0.3)
         * @return True when Vehicle moves
         */
        bool isMoving() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_VEHICLE_H
