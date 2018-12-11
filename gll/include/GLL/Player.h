#ifndef ROADFIGHTER_PLAYER_H
#define ROADFIGHTER_PLAYER_H

#include "Vehicle.h"

namespace RoadFighter {

    /**
     * This class represents the Player
     * This class is derived from @see Vehicle
     */
    class Player : public Vehicle {
    public:
        /**
         * This function accelerates the Player
         */
        void accelerate() override;

        /**
         * Virtual function to determine whether an Entity can be destroyed or not
         * @return False, a player cannot be destroyed during the process of the game
         */
        bool canBeDestroyed() const override;

        /**
         * Virtual function to determine whether the Entity is a Player
         * @return True
         */
        bool isPlayer() const override;

        /**
         * Default constructor for the Player
         * Initializes the location of the player on (-0.25, -2)
         */
        Player();

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
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PLAYER_H
