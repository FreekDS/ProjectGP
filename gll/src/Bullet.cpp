
#include <GLL/Bullet.h>

#include "GLL/Bullet.h"

RoadFighter::Bullet::Bullet(double m_shootSpeed)
        :m_shootSpeed(m_shootSpeed) { }

RoadFighter::Bullet::Bullet() : m_shootSpeed(0) { }

RoadFighter::Bullet& RoadFighter::Bullet::operator=(const RoadFighter::Bullet& other)
{
    if(this == &other)
        return *this;
    m_shootSpeed = other.m_shootSpeed;
    return *this;
}

double RoadFighter::Bullet::getShootSpeed() const
{
    return m_shootSpeed;
}

void RoadFighter::Bullet::setShootSpeed(double speed)
{
    Bullet::m_shootSpeed = speed;
}

RoadFighter::Bullet::~Bullet() = default;
