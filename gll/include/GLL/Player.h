#ifndef ROADFIGHTER_PLAYER_H
#define ROADFIGHTER_PLAYER_H

#include "Vehicle.h"

namespace RoadFighter {

    class Player : public Vehicle {
    public:
        void accelerate() override;

        bool canBeDestroyed() override;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_PLAYER_H
