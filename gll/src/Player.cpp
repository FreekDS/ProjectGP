#include <GLL/Player.h>
#include <GLL/Transformation.h>
#include <iostream>

namespace RoadFighter {

    /**
     * This function accelerates the Player.
     */
    void Player::accelerate()
    {
        if(getSpeed() < m_maxSpeed)
            setSpeed(getSpeed() + 0.01);
        if(getSpeed() > m_maxSpeed)
            setSpeed(getSpeed() - 0.01);
        notify();
    }

    /**
     * Virtual function to determine whether an Entity can be destroyed or not.
     * @return False, a player cannot be destroyed during the process of the game.
     */
    bool Player::canBeDestroyed() const
    {
        return false;
    }

    /**
     * Default constructor for the Player.
     * Initializes the location of the player on (-0.25, -2).
     * Initializes the collider of the player on its bounds.
     * Sets the type of the entity to Player
     * Initializes the repair time.
     */
    Player::Player() : m_maxSpeed(20), m_maxSpeedWhenMovingUp(22), m_shootDelayTime(1750), m_shootDelay(m_shootDelayTime)
    {
        double width = 0.24;
        double height = 0.40;
        initializeCorners(width, height);
        setPos(-0.25, -2);
        setType(EntityType::PLAYER);
        setRepairTime(1000);
    }

    /**
     * Moves the player to the left.
     */
    void Player::moveLeft(double world_boundary)
    {
        if(isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(-getMovespeed(), 0);
            if (getUpperLeftCorner().x<world_boundary)
                updatePos(getMovespeed()+0.000001, 0);
        }
    }

    /**
     * Moves the player to the right.
     */
    void Player::moveRight(double world_boundary)
    {
        if(isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(getMovespeed(), 0);
            if (getBottomRightCorner().x>world_boundary)
                updatePos(-getMovespeed()-0.000001, 0);
        }
    }

    /**
     * Moves the player up.
     * If the player is on top of the screen, it will not move further up.
     */
    void Player::moveUp()
    {
        if(isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getUpperLeftCorner())) {
                updatePos(0, getMovespeed());
                if (getSpeed()<m_maxSpeedWhenMovingUp)
                    setSpeed(getSpeed()+0.03);
                notify();
            }
        }
    }

    /**
     * Moves the player down.
     * If the player is on the bottom of the screen, it will not move further down.
     */
    void Player::moveDown()
    {
        if(isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getBottomRightCorner())) {
                updatePos(0, -getMovespeed());
                setSpeed(getSpeed()-0.015);
                notify();
            }
        }
    }

    /**
     * Attaches an observer to the player.
     * @param observer Observer to attach to the player.
     */
    void Player::attach(const shared_ptr<Observer>& observer)
    {
        m_observers.push_back(observer);
    }

    /**
     * Notifies all observers of made changes.
     */
    void Player::notify() const
    {
        for(const observer_ptr& observer : m_observers) {
            observer->update();
        }
    }

    /**
     * This function slows the player down when not accelerating.
     */
    void Player::slowDown()
    {
        if(getSpeed() > 0) {
            setSpeed(getSpeed()-0.02);
        }
        if(getSpeed() < 0)
            setSpeed(0);
        notify();
    }

    /**
     * Getter for the max speed of the Player.
     * @param whenPressed If this value is true, the function returns the max speed when the up key is pressed.
     * @return max speed of the player.
     */
    double Player::getMaxSpeed(bool whenPressed) const
    {
        if(whenPressed)
            return m_maxSpeedWhenMovingUp;
        else
            return m_maxSpeed;
    }

    /**
     * Virtual function to update the entity.
     * - Resets the rotation of the sprite.
     * - Handles the crash if one happened.
     */
    void Player::update()
    {
        if(hasCrashed()){
            setSpeed(0);
            rotateSprite(10);
            if(repair()){
                for(auto& observer : m_observers){
                    if(observer->getType() == ObserverType::SCORE){
                        auto obs = dynamic_pointer_cast<ScoreObserver>(observer);
                        obs->updateScore(-100);
                    }
                }
            }
        }else {
            setSpriteRotation(0);
        }
    }

    /**
     * Sets the covered distance of the player.
     * @param distanceCovered Covered distance of the player.
     */
    void Player::setDistanceCovered(double distanceCovered)
    {
        m_coveredDistance = distanceCovered;
    }

    /**
     * Gets the covered distance of the player
     * @return Covered distance of the player
     */
    double Player::getCoveredDistance() const
    {
        return m_coveredDistance;
    }

    /**
     * Getter for the observers of the player
     * @return Vector of shared pointers to the observers
     */
    const vector<observer_ptr>& Player::getObservers() const
    {
        return m_observers;
    }

    /**
     * Handles the shoot delay timer.
     * @return True if the player can shoot. Else false.
     */
    bool Player::shoot()
    {
        if(!m_shootDelay.timerRunning()){
            m_shootDelay.setTimer(m_shootDelayTime);
            m_shootDelay.startTimer();
            return false;
        }
        else{
            if(m_shootDelay.timerFinished()){
                m_shootDelay.reset();
                return true;
            }
            else{
                return false;
            }
        }
    }

    /**
     * Updates the score of the player.
     * @param score Amount to increase score
     */
    void Player::updateScore(int score)
    {
        for(auto& obs : m_observers){
            if(obs->getType() == ObserverType::SCORE){
                dynamic_pointer_cast<ScoreObserver>(obs)->updateScore(score);
                break;
            }
        }
    }

} // namespace RoadFighter
