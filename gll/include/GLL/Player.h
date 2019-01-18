#ifndef ROADFIGHTER_PLAYER_H
#define ROADFIGHTER_PLAYER_H

#include "Vehicle.h"
#include "Observer.h"

namespace RoadFighter {

    using observer_ptr = shared_ptr<Observer>;

    /**
     * This class represents the Player.
     * This class is derived from @see Vehicle.
     * A player has:
     * - all attributes of a vehicle.
     * - a max speed.
     * - a max speed when the up key is pressed.
     * - a vector of observers (observer design pattern).
     */
    class Player : public Vehicle {
    private:
        double m_maxSpeed;
        double m_maxSpeedWhenMovingUp;
        double m_coveredDistance;
    protected:
        vector<observer_ptr> m_observers;
    public:
        /**
         * Default constructor for the Player.
         * Initializes the location of the player on (-0.25, -2).
         * Initializes the collider of the player on its bounds.
         * Sets the type of the entity to Player
         * Initializes the repair time.
         */
        Player();

        /**
         * This function accelerates the Player.
         */
        void accelerate() override;

        /**
         * This function slows the player down when not accelerating.
         */
        void slowDown() override;

        /**
         * Virtual function to determine whether an Entity can be destroyed or not.
         * @return False, a player cannot be destroyed during the process of the game.
         */
        bool canBeDestroyed() const override;

        /**
         * Moves the player to the left.
         */
        void moveLeft(double world_boundary) override;

        /**
         * Moves the player to the right.
         */
        void moveRight(double world_boundary) override;

        /**
         * Moves the player up.
         * If the player is on top of the screen, it will not move further up.
         */
        void moveUp() override;

        /**
         * Moves the player down.
         * If the player is on the bottom of the screen, it will not move further down.
         */
        void moveDown() override;

        /**
         * Attaches an observer to the player.
         * @param observer Observer to attach to the player.
         */
        void attach(const observer_ptr& observer);

        /**
         * Notifies all observers of made changes.
         */
        void notify() const;

        /**
         * Getter for the max speed of the Player.
         * @param whenPressed If this value is true, the function returns the max speed when the up key is pressed.
         * @return max speed of the player.
         */
        double getMaxSpeed(bool whenPressed = true) const;

        /**
         * Sets the absolute rotation of the sprite.
         * @param angle The angle over which the sprite needs to be rotated.
         */
        virtual void setSpriteRotation(float angle) = 0;

        /**
         * Rotates the sprite relative to its previous rotation.
         * @param angle Angle over which the sprite needs to be rotated.
         */
        virtual void rotateSprite(float angle) = 0;

        /**
         * Virtual function to update the entity.
         * - Resets the rotation of the sprite.
         * - Handles the crash if one happened.
         */
        void update() override;

        /**
         * Sets the covered distance of the player.
         * @param distanceCovered Covered distance of the player.
         */
        void setDistanceCovered(double distanceCovered);

        /**
         * Gets the covered distance of the player
         * @return Covered distance of the player
         */
        double getCoveredDistance() const;

        /**
         * Getter for the observers of the player
         * @return Vector of shared pointers to the observers
         */
        const vector<observer_ptr>& getObservers() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PLAYER_H
