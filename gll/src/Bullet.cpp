
#include <GLL/Bullet.h>
#include <GLL/Transformation.h>

#include "GLL/Bullet.h"

namespace RoadFighter {

    /**
     * Constructor for Bullet.
     * @param shootSpeed shooting speed of the bullet.
     */
    Bullet::Bullet(double shootSpeed, const Position& playerPos, double playerHeight)
            :m_shootSpeed(shootSpeed), m_hit(false) {
        setType(EntityType::BULLET);
        double width = 0.06;
        double height = 0.10;
        initializeCorners(width, height);
        setPos(playerPos.x, playerPos.y + playerHeight + getHeight());
    }

    /**
     * Assignment operator for Bullet.
     * @param other The other bullet.
     * @return Reference to bullet which is equal to other.
     */
    Bullet& Bullet::operator=(const RoadFighter::Bullet& other)
    {
        if (this==&other)
            return *this;
        m_shootSpeed = other.m_shootSpeed;
        return *this;
    }

    /**
     * Getter for the shooting speed of the Bullet.
     * @return Shooting speed of the Bullet.
     */
    double Bullet::getShootSpeed() const
    {
        return m_shootSpeed;
    }

    /**
     * Setter for the shooting speed of the Bullet.
     * @param speed New shooting speed for the Bullet.
     */
    void Bullet::setShootSpeed(double speed)
    {
        Bullet::m_shootSpeed = speed;
    }

    void Bullet::update()
    {
        updatePos(0,m_shootSpeed);
        updateSpriteLocation();
    }

    void Bullet::hit()
    {
        m_hit = true;
    }

    bool Bullet::canBeDestroyed() const
    {
        auto trans = Transformation::getInstance();
        return m_hit || getPos().y > trans->getYRange().second * 2;
    }

    /**
     * Default destructor for Bullet.
     */
    Bullet::~Bullet() = default;

} // namespace RoadFighter