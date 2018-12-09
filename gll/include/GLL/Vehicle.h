#ifndef ROADFIGHTER_VEHICLE_H
#define ROADFIGHTER_VEHICLE_H

#include "Entity.h"

namespace RoadFighter {

    /**
     * This is an abstract class which represents a Vehicle
     * This class is derived from @see Entity
     * A vehicle has:
     * - a driving speed
     */
    class Vehicle : public Entity {
    private:
        double m_speed;
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
         * Pure virtual function to move the vehicle to the left
         */
        virtual void moveLeft() = 0;

        /**
         * Pure virtual function to move the vehicle to the right
         */
        virtual void moveRight() = 0;

        /**
         * Pure virtual function to move the vehicle up
         */
        virtual void moveUp() = 0;

        /**
         * Pure virtual function to move the vehicle down
         */
        virtual void moveDown() = 0;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_VEHICLE_H
