#ifndef ROADFIGHTER_ENTITY_H
#define ROADFIGHTER_ENTITY_H

namespace RoadFighter {

    class Entity {
    public:
        Entity();
        Entity(const Entity& other);
        Entity& operator=(const Entity& other);
        Entity(Entity&& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;
        virtual ~Entity();
    };

}

#endif //ROADFIGHTER_ENTITY_H
