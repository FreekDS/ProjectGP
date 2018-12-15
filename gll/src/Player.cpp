#include <GLL/Player.h>
#include <GLL/Transformation.h>
#include <iostream>

namespace RoadFighter {

    /**
     * This function accelerates the Player
     */
    void Player::accelerate()
    {
        notify();
    }

    /**
     * Virtual function to determine whether an Entity can be destroyed or not
     * @return False, a player cannot be destroyed during the process of the game
     */
    bool Player::canBeDestroyed() const
    {
        return false;
    }

    /**
     * Virtual function to determine whether the Entity is a Player
     * @return True
     */
    bool Player::isPlayer() const
    {
        return true;
    }

    /**
     * Default constructor for the Player
     * Initializes the location of the player on (-0.25, -2)
     * Initializes the collider of the player on its bounds
     */
    Player::Player()
    {
        double width = 0.24;
        double height = 0.45;
        setUpperLeftCorner({-width/2, height/2});
        setBottomRightCorner({width/2,-height/2});
        BoxCollider collider(getUpperLeftCorner(), getBottomRightCorner());
        addCollider(collider);
    }

    /**
     * Moves the player to the left
     */
    void Player::moveLeft(double world_boundary)
    {
        auto trans = Transformation::getInstance();
        if (trans->isInGrid(getPos()))
            updatePos(-getMovespeed(), 0);
        if(getUpperLeftCorner().x < world_boundary)
            updatePos(getMovespeed()+ 0.000001, 0);

    }

    /**
     * Moves the player to the right
     */
    void Player::moveRight(double world_boundary)
    {
        auto trans = Transformation::getInstance();
        if (trans->isInGrid(getPos()))
            updatePos(getMovespeed(), 0);
        if(getBottomRightCorner().x > world_boundary)
            updatePos(-getMovespeed() - 0.000001, 0);
    }

    /**
     * Moves the player up
     * If the player is on top of the screen, it will not move further up
     */
    void Player::moveUp()
    {
        auto trans = Transformation::getInstance();
        if (trans->isInGrid(getUpperLeftCorner()))
            updatePos(0, getMovespeed());
    }

    /**
     * Moves the player down
     * If the player is on the bottom of the screen, it will not move further down
     */
    void Player::moveDown()
    {
        auto trans = Transformation::getInstance();
        if (trans->isInGrid(getBottomRightCorner()))
            updatePos(0, -getMovespeed());
    }

    /**
     * Attaches an observer to the player
     * @param observer Observer to attach to the player
     */
    void Player::attach(const shared_ptr<Observer>& observer)
    {
        m_observers.push_back(observer);
    }

    /**
     * Notifies all observers of made changes
     */
    void Player::notify() const
    {
        for(const observer_ptr& observer : m_observers) {
            observer->update();
        }
    }

} // namespace RoadFighter
