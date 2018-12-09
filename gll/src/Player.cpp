#include <GLL/Player.h>
#include <GLL/Transformation.h>

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

    Player::Player() {
        setPos(-0.25, -2);

    }

    void Player::moveLeft()
    {
        auto trans = Transformation::getInstance();
        if(trans->isInGrid(getPos()))
            updatePos(-0.001, 0);
    }

    void Player::moveRight()
    {
        auto trans = Transformation::getInstance();
        if(trans->isInGrid(getPos()))
            updatePos(0.001, 0);
    }

    void Player::moveUp()
    {
        auto trans = Transformation::getInstance();
        // todo remove second part
        if(trans->isInGrid(getUpperLeftCorner()) || getPos().y < trans->getYRange().second)
            updatePos(0, 0.001);
    }

    void Player::moveDown()
    {
        auto trans = Transformation::getInstance();
        // todo remove second part
        if(trans->isInGrid(getBottomRightCorner()) || getPos().y > trans->getYRange().first)
            updatePos(0, -0.001);
    }

} // namespace RoadFighter
