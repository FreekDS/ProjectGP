#include <GLL/Entity.h>
#include <GLL/Transformation.h>
#include <cmath>

namespace RoadFighter {

    Entity::Entity()
            :m_pos(Position()), m_cornerUL(Position()), m_cornerBR(Position()) { }

    Entity::~Entity() = default;

    Entity::Entity(const Entity& other) = default;

    Entity& Entity::operator=(const Entity& other)
    {
        if (this==&other)
            return *this;
        m_pos = other.m_pos;
        m_cornerBR = other.m_cornerBR;
        m_cornerUL = other.m_cornerUL;
        return *this;
    }

    Entity::Entity(Entity&& other) noexcept
            :m_pos(other.m_pos), m_cornerUL(other.m_cornerUL), m_cornerBR(other.m_cornerBR) { }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this==&other)
            return *this;
        m_pos = other.m_pos;
        m_cornerBR = other.m_cornerBR;
        m_cornerUL = other.m_cornerUL;
        return *this;
    }

    bool Entity::isVisible() const
    {
        auto trans = Transformation::getInstance();
        range xRange = trans->getXRange();
        range yRange = trans->getYRange();
        return m_pos.x<xRange.first || m_pos.x>xRange.second || m_pos.y<yRange.first || m_pos.y>yRange.second;
    }

    const Position& Entity::getPos() const
    {
        return m_pos;
    }

    void Entity::setPos(const Position& pos)
    {
        Entity::m_pos = pos;
    }

    const Position& Entity::getUpperRightCorner() const
    {
        return m_cornerUL;
    }

    const Position& Entity::getBottomRightCorner() const
    {
        return m_cornerBR;
    }

    void Entity::setUpperLeftCorner(const Position& cornerUpLeft)
    {
        Entity::m_cornerUL = cornerUpLeft;
    }

    void Entity::setBottomRightCorner(const Position& cornerBottomRight)
    {
        Entity::m_cornerBR = cornerBottomRight;
    }

    double Entity::getWidth() const
    {
        return fabs(m_cornerUL.x-m_cornerBR.x);
    }

    double Entity::getHeight() const
    {
        return fabs(m_cornerUL.y-m_cornerBR.y);
    }

    bool Entity::isPlayer() const
    {
        return false;
    }

} // namespace RoadFighter
