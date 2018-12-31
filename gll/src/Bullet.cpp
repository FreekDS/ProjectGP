#include "GLL/Bullet.h"

namespace RoadFighter {

    /**
     * Constructor for Bullet.
     * @param shootSpeed shooting speed of the bullet.
     */
    Bullet::Bullet(double shootSpeed)
            :m_shootSpeed(shootSpeed) {
        setType(EntityType::BULLET);
    }

    /**
     * Default constructor for Bullet.
     */
    Bullet::Bullet()
            :m_shootSpeed(0) { }

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

    /**
     * Default destructor for Bullet.
     */
    Bullet::~Bullet() = default;

} // namespace RoadFighter