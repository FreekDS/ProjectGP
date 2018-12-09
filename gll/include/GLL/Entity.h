#ifndef ROADFIGHTER_ENTITY_H
#define ROADFIGHTER_ENTITY_H

#include "Position.h"

namespace RoadFighter {

    class Entity {
    private:
        Position m_pos;
        Position m_cornerUL;
        Position m_cornerBR;
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

        virtual void draw() const = 0;
        virtual void update() = 0;
        virtual bool canBeDestroyed() const = 0;

        virtual bool isPlayer() const;

        const Position& getPos() const;
        const Position& getUpperLeftCorner() const;
        const Position& getBottomRightCorner() const;

        void setPos(const Position& pos);
        void setPos(double x, double y);
        void setUpperLeftCorner(const Position& cornerUpLeft);
        void setBottomRightCorner(const Position& cornerBottomRight);

        double getWidth() const;
        double getHeight() const;

        void updatePos(double x, double y);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ENTITY_H
