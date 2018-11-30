#ifndef ROADFIGHTER_ENTITY_H
#define ROADFIGHTER_ENTITY_H

#include "Position.h"

namespace RoadFighter {

    class Entity {
    private:
        Position m_pos;
    public:
        Entity();
        Entity(const Entity& other);
        Entity& operator=(const Entity& other);
        Entity(Entity&& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;
        virtual ~Entity();

        /**
         * Checks whether the Entity is in the coordinate system of the game logic
         * @return True if the position is in [-4,4] x [-3,3]
         */
        bool isVisible() const;

        const Position& getPos() const;
        void setPos(const Position& pos);

        virtual void draw() const = 0;
        virtual void update() = 0;
        virtual bool canBeDestroyed() = 0;
    };

}

#endif //ROADFIGHTER_ENTITY_H
