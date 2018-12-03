
#include <GLL/Entity.h>
#include <GLL/Transformation.h>


namespace RoadFighter {

    Entity::Entity() : m_pos(Position()) {}

    Entity::~Entity() = default;

    Entity::Entity(const Entity& other) = default;

    Entity& Entity::operator=(const Entity& other)
    {
        if(this == &other)
            return *this;
        m_pos = other.m_pos;
        return *this;
    }

    Entity::Entity(Entity&& other) noexcept : m_pos(other.m_pos) {}

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if(this == &other)
            return *this;
        m_pos = other.m_pos;
        return *this;
    }

    bool Entity::isVisible() const
    {
        return m_pos.x < -4.0 || m_pos.x > 4.0 || m_pos.y < -3.0 || m_pos.y > 3.0;
    }

    const Position& Entity::getPos() const
    {
        return m_pos;
    }

    void Entity::setPos(const Position& pos)
    {
        Entity::m_pos = pos;
    }

} // namespace RoadFighter
