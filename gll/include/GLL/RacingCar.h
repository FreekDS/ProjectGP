#ifndef ROADFIGHTER_RACINGCAR_H
#define ROADFIGHTER_RACINGCAR_H

#include "Vehicle.h"
#include "Player.h"
#include "World.h"


namespace RoadFighter {

    /**
     * Represents the range of the speed.
     * The first double is the minimum speed, the second is the maximum speed.
     */
    using speedRange = pair<double, double>;

    /**
     * This enumeration represents all possible moves.
     */
    enum move{
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

    /**
     * This class represents a racing car.
     * This class is derived from @see Vehicle.
     * A racing car has:
     * - A shared pointer to the player.
     * - A shared pointer to the world.
     * - A speed range.
     * - A boolean to determine whether the car has reached the finish or not.
     * - The last move the car made.
     * - A move cooldown clock.
     * - A cooldown time.
     * - An ID.
     * - A boolean to check if the game has started.
     * - A movement speed (double).
     */
    class RacingCar : public Vehicle {
    private:
        shared_ptr<Player> m_player;
        shared_ptr<World> m_world;
        speedRange m_range;
        bool m_finished;
        move m_lastMoveHorizontal;
        Clock m_moveCooldown;
        const int m_cooldownTime;
        const int m_id;
        bool m_gameStarted;
        double m_moveSpeed;

        /**
         * Static counter to count instances of this class.
         * Used to initialize the positions of the cars.
         * @see initializePosition()
         */
        static unsigned int CAR_COUNT;

        /**
         * Initializes the position of the car based on the car count.
         */
        void initializePosition();

        /**
         * Updates the movement speed of the Racing car.
         */
        void updateMoveSpeed();

    public:
        /**
         * Default destructor of Racing car.
         */
        ~RacingCar() override;

        /**
         * Constructor of Racing car.
         * This constructor also initializes the corners and position, the cooldown timer, the move speed, the repair
         * time, the last move the car made, the cooldown time and the ID. The static value of CAR_COUNT is
         * increased by one.
         * @param player Shared pointer to the player.
         * @param world Shared pointer to the world.
         */
        RacingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world);

        /**
         * Accelerates the racing car.
         */
        void accelerate() override;

        /**
         * Updates the race car every game tick.
         * Updates the location of the sprite.
         *
         * First phase: the player has not started moving:
         * - We don't do anything, whenever the player starts moving, we move to phase two.
         *
         * Second phase: the player started moving, but the speed is lower than the minimum speed
         * - First we move the racing car up or down depending on the player's speed.
         * - We have to accelerate 100% of the time.
         * - If the speed is greater than the minimum, phase three starts.
         *
         * Third phase: the game is running normal
         * - Randomly accelerate
         * - Randomly slow down
         * - Update the move speed depending on the speed deficit with the player
         * - Randomly move left
         * - Randomly move right
         * - Move up or down depending on the player speed
         *
         * If the car finished the race, don't do anything.
         */
        void update() override;

        /**
         * Determine if the car can be destroyed.
         * @return False, a race car cannot be destroyed.
         */
        bool canBeDestroyed() const override;

        /**
         * Slows down the racing car.
         */
        void slowDown() override;

        /**
         * Moves the player to the left if possible.
         * @param world_boundary Left boundary of the world.
         */
        void moveLeft(double world_boundary) override;

        /**
         * Moves the player to the right if possible.
         * @param world_boundary Right boundary of the world.
         */
        void moveRight(double world_boundary) override;

        /**
         * Moves the race car up on the screen.
         */
        void moveUp() override;

        /**
         * Moves the race car down on the screen.
         */
        void moveDown() override;

        /**
         * Does the horizontal movement.
         * @see update()
         */
        void doHorizontalMovement();

        /**
         * Updates the speed of the race car.
         * @see update()
         */
        void updateSpeedRandom();

        /**
         * Rotates the sprite over an angle relative to the current rotation.
         * @param angle Angle to rotate over.
         */
        virtual void rotateSprite(float angle) = 0;

        /**
         * Sets the absolute rotation of the sprite.
         * @param angle Rotation angle to set.
         */
        virtual void setSpriteRotation(float angle) = 0;

        bool carInPath() const;
    };


} // namespace RoadFighter

#endif //ROADFIGHTER_RACINGCAR_H
