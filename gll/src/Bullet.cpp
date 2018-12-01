#include "GLL/Bullet.h"

namespace RoadFighter {

    Bullet::Bullet(double m_shootSpeed)
            :m_shootSpeed(m_shootSpeed) { }

    Bullet::Bullet()
            :m_shootSpeed(0) { }

    Bullet& Bullet::operator=(const RoadFighter::Bullet& other)
    {
        if (this==&other)
            return *this;
        m_shootSpeed = other.m_shootSpeed;
        return *this;
    }

    double Bullet::getShootSpeed() const
    {
        return m_shootSpeed;
    }

    void Bullet::setShootSpeed(double speed)
    {
        Bullet::m_shootSpeed = speed;
    }

    Bullet::~Bullet() = default;

} // namespace RoadFighter