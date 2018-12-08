#include <GLL/Player.h>

namespace RoadFighter {

    void Player::accelerate()
    {

    }

    bool Player::canBeDestroyed() const
    {
        return false;
    }

    bool Player::isPlayer() const
    {
        return true;
    }

} // namespace RoadFighter
