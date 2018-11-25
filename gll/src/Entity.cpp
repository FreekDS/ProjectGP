
#include <GLL/Entity.h>

#include "GLL/Entity.h"

namespace RoadFighter {

    Entity::Entity() = default;

    Entity::~Entity() = default;

    Entity::Entity(const Entity& other) = default;

    Entity& Entity::operator=(const Entity& other)
    {
        if(this == &other)
            return *this;
        // copy items
        return *this;
    }

    Entity::Entity(Entity&& other) noexcept
    {

    }

    Entity& Entity::operator=(Entity&& other) noexcept
    {
        return *this;
    }
}
