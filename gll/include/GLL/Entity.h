#ifndef ROADFIGHTER_ENTITY_H
#define ROADFIGHTER_ENTITY_H

#include "Position.h"
#include "BoxCollider.h"

namespace RoadFighter {

    /**
     * Enumeration of all different Entity types.
     */
    enum EntityType{
        PLAYER,
        WORLD,
        BULLET,
        PASSING_CAR,
        RACE_CAR,
        FINISH,
        VEHICLE,
        UNKNOWN
    };

    /**
     * Abstract base class of all Entities.
     * Each entity has a position (= the center of the Entity).
     * And two corner positions:
     * - The upper left corner.
     * - The bottom right corner.
     * - A vector of box colliders.
     * - A type.
     */
    class Entity {
    private:
        Position m_pos;
        Position m_cornerUL;
        Position m_cornerBR;
        vector<BoxCollider> m_colliders;
        EntityType m_type = EntityType::UNKNOWN;

    protected:
        /**
         * Setter for the type of the Entity.
         * @param type Type of the entity.
         */
        void setType(const EntityType& type);

    public:
        /**
         * Default constructor of Entity.
         * Initializes the position, and both corners on (0,0).
         */
        Entity();

        /**
         * Copy constructor of Entity.
         * @param other Const reference to entity which needs to be copied.
         */
        Entity(const Entity& other);

        /**
         * Getter for colliders.
         * @return Vector of box colliders.
         */
        const vector<BoxCollider>& getColliders() const;

        /**
         * Assignment operator of Entity.
         * @param other Const reference to other entity.
         * @return Reference to Entity which is equal to other.
         */
        Entity& operator=(const Entity& other);

        /**
         * Move constructor of Entity.
         * @param other Entity to move.
         */
        Entity(Entity&& other) noexcept;

        /**
         * Move assignment operator.
         * @param other Entity to move.
         * @return Reference to entity which is equal to the original other.
         */
        Entity& operator=(Entity&& other) noexcept;

        /**
         * Default destructor for Entity.
         */
        virtual ~Entity();

        /**
         * Checks whether the Entity is in the coordinate system of the game logic.
         * @return True if the position is in [-4,4] x [-3,3].
         */
        bool isVisible() const;

        /**
         * Virtual function to draw the entity.
         */
        virtual void draw() const = 0;

        /**
         * Virtual function to update the entity.
         */
        virtual void update() = 0;

        /**
         * Virtual function to determine whether an Entity can be destroyed or not.
         * @return True if the entity can be destroyed.
         */
        virtual bool canBeDestroyed() const = 0;

        /**
         * Getter for Position of entity.
         * @return Const reference to entity position.
         */
        const Position& getPos() const;

        /**
         * Getter for upper left corner of the Entity.
         * @return Const reference to Position of the upper left corner.
         */
        const Position& getUpperLeftCorner() const;

        /**
         * Getter for the bottom right corner of the Entity.
         * @return Const reference to Position of bottom right corner.
         */
        const Position& getBottomRightCorner() const;

        /**
         * Setter for Position of Entity.
         * @param pos New position for Entity.
         */
        void setPos(const Position& pos);

        /**
         * Setter for position of Entity.
         * @param x X value of Position of Entity.
         * @param y Y value of Position of Entity.
         */
        void setPos(double x, double y);

        /**
         * Setter for upper left corner of Entity.
         * @param cornerUpLeft New Position of upper left corner.
         */
        void setUpperLeftCorner(const Position& cornerUpLeft);

        /**
         * Setter for bottom right corner of Entity.
         * @param cornerBottomRight New Position of bottom right corner.
         */
        void setBottomRightCorner(const Position& cornerBottomRight);

        /**
         * Calculates the width of the Entity based on the two corners.
         * @return Width of Entity.
         */
        double getWidth() const;

        /**
         * Calculates the height of the Entity based on the two corners.
         * @return Height of the Entity.
         */
        double getHeight() const;

        /**
         * Updates the position of the entity.
         * This function also updates the two corners respectively.
         * @param x X value to add to the Position.
         * @param y Y value to add to the Position.
         */
        void updatePos(double x, double y);

        /**
         * Adds a collider to the Entity.
         * @param collider Collider to add to the entity.
         */
        void addCollider(const BoxCollider& collider);

        /**
         * Removes a collider form the Entity.
         * @param i Index of collider to remove.
         */
        void removeCollider(int i);

        /**
         * Initializes the upper left and the bottom right corner.
         * This function also adds a collider to the entity.
         * Make sure the position is (0,0) when this function gets called.
         * If there is another position, it will be reset to (0,0).
         * @param width Width of the entity.
         * @param height Height of the entity.
         */
        void initializeCorners(double width, double height);

        /**
         * Pure virtual function to update the location of the sprite.
         */
        virtual void updateSpriteLocation() = 0;

        /**
         * Getter for the type of the Entity
         * @return Type of the entity.
         */
        EntityType getType() const;

        /**
         * Disable all the colliders of the entity.
         */
        void disableColliders();
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_ENTITY_H
