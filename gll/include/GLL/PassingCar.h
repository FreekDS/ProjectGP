#ifndef ROADFIGHTER_PASSINGCAR_H
#define ROADFIGHTER_PASSINGCAR_H

#include "Vehicle.h"
#include "World.h"
#include "Player.h"

namespace RoadFighter {

    /**
     * This class represents a passing car.
     * This class is derived from @see Entity.
     * A passing car has:
     * - A shared pointer of the player.
     * - A shared pointer to the world.
     */
    class PassingCar : public Vehicle {
    private:
        shared_ptr<Player> m_player;
        shared_ptr<World> m_world;
    public:
        /**
         * Constructor of PassingCar taking the speed of the vehicle.
         * @param speed Speed of the vehicle.
         * @param player Shared pointer to the Player.
         * @param world Shared pointer to the world.
         */
        PassingCar(double speed, const shared_ptr<Player>& player, const shared_ptr<World>& world);

        /**
         * Constructor of PassingCar taking the Player and World as parameter.
         * @param player Shared pointer to the Player.
         * @param world Shared pointer to the World.
         */
        PassingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world);

        /**
         * Default destructor of PassingCar.
         */
         ~PassingCar() override;

         /**
          * Updates the PassingCar.
          */
        void update() override;

        /**
         * Determine whether the PassingCar can be destroyed or not.
         * A PassingCar can be destroyed if it's Y position is lower than 2 times the minimum Y
         * or if it's Y position is greater than 2 times the maximum Y.
         * This minimum and maximum are obtained from @see Transformation
         * @return True if the PassingCar can be destroyed
         */
        bool canBeDestroyed() const override;

        /**
         * Accelerates the PassingCar.
         * This function does nothing, a passing car drives at a constant speed.
         */
        void accelerate() override {}

        /**
         * Slows down the PassingCar.
         * This function does nothing, a passing car drives at constant speed.
         */
        void slowDown() override {}

        /**
         * Moves the PassingCar to the left.
         * This function is not used, a passing car cannot move left.
         * @param world_boundary
         */
        void moveLeft(double world_boundary) override {}

        /**
         * Moves the PassingCar to the right.
         * This function is not used, a passing car cannot move right.
         * @param world_boundary Right boundary of the world
         */
        void moveRight(double world_boundary) override {}

        /**
         * Moves the PassingCar up on the screen.
         */
        void moveUp() override;

        /**
         * Moves the PassingCar down on the screen.
         */
        void moveDown() override;

        /**
         * Initializes the position randomly inside the World.
         * The position will be initialized in between the two boundaries of the World.
         */
        void initializePosition();
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PASSINGCAR_H
