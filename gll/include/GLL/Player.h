#ifndef ROADFIGHTER_PLAYER_H
#define ROADFIGHTER_PLAYER_H

#include "Vehicle.h"
#include "Observer.h"

namespace RoadFighter {

    using observer_ptr = shared_ptr<Observer>;

    /**
     * This class represents the Player
     * This class is derived from @see Vehicle
     * A player has:
     * - all attributes of a vehicle
     * - a vector of observers (observer design pattern)
     */
    class Player : public Vehicle {
    private:
        double m_maxSpeed;
        double m_maxSpeedWhenMovingUp;
    protected:
        vector<observer_ptr> m_observers;
    public:
        /**
         * Default constructor for the Player
         * Initializes the location of the player on (-0.25, -2)
         */
        Player();

        /**
         * This function accelerates the Player
         */
        void accelerate() override;

        /**
         * This function slows the player down when not accelerating
         */
        void slowDown() override;

        /**
         * Virtual function to determine whether an Entity can be destroyed or not
         * @return False, a player cannot be destroyed during the process of the game
         */
        bool canBeDestroyed() const override;

        /**
         * Overridden function to determine whether the Entity is a Player
         * @return True
         */
        bool isPlayer() const override;

        /**
         * Moves the player to the left
         */
        void moveLeft(double world_boundary) override;

        /**
         * Moves the player to the right
         */
        void moveRight(double world_boundary) override;

        /**
         * Moves the player up
         * If the player is on top of the screen, it will not move further up
         */
        void moveUp() override;

        /**
         * Moves the player down
         * If the player is on the bottom of the screen, it will not move further down
         */
        void moveDown() override;

        /**
         * Attaches an observer to the player
         * @param observer Observer to attach to the player
         */
        void attach(const observer_ptr& observer);

        /**
         * Notifies all observers of made changes
         */
        void notify() const;

        /**
         * Getter for the max speed of the Player
         * @param whenPressed If this value is true, the function returns the max speed when the up key is pressed
         * @return max speed of the player
         */
        double getMaxSpeed(bool whenPressed = true) const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PLAYER_H
