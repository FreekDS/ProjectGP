#ifndef ROADFIGHTER_RACINGCAR_H
#define ROADFIGHTER_RACINGCAR_H

#include "Vehicle.h"
#include "Player.h"
#include "World.h"


namespace RoadFighter {

    using speedRange = pair<double, double>;

    enum move{
        LEFT,
        RIGHT,
        NONE
    };

    /**
     * This class represents a racing car
     * This class is derived from @see Vehicle
     */
    class RacingCar : public Vehicle {
    private:
        shared_ptr<Player> m_player;
        shared_ptr<World> m_world;
        speedRange m_range;
        bool m_finished;
        move m_lastMove;

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

        void updateMoveSpeed();

    public:

        ~RacingCar() override;

        RacingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world);

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

        bool canBeDestroyed() const override;

        void slowDown() override;

        void moveLeft(double world_boundary) override;

        void moveRight(double world_boundary) override;

        void moveUp() override;

        void moveDown() override;

        void finish();

        bool hasFinished() const;

    };

} // namespace RoadFighter

#endif //ROADFIGHTER_RACINGCAR_H
