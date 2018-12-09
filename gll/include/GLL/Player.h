#ifndef ROADFIGHTER_PLAYER_H
#define ROADFIGHTER_PLAYER_H

#include "Vehicle.h"

namespace RoadFighter {

    class Player : public Vehicle {
    public:
        void accelerate() override;

        bool canBeDestroyed() const override;

        bool isPlayer() const override;

        Player();

        void moveLeft() override;

        void moveRight() override;

        void moveUp() override;

        void moveDown() override;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PLAYER_H
