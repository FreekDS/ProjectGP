#include <GLL/Entity.h>
#include <GLL/Transformation.h>
#include <cmath>

namespace RoadFighter {

    /**
     * Default constructor of Entity.
     * Initializes the position, and both corners on (0,0).
     */
    Entity::Entity()
            :m_pos(Position()), m_cornerUL(Position()), m_cornerBR(Position()), m_type(EntityType::UNKNOWN) { }

    /**
     * Default destructor for Entity.
     */
    Entity::~Entity() = default;

    /**
     * Copy constructor of Entity.
     * @param other Const reference to entity which needs to be copied.
     */
    Entity::Entity(const Entity& other) = default;

    /**
     * Assignment operator of Entity.
     * @param other Const reference to other entity.
     * @return Reference to Entity which is equal to other.
     */
    Entity& Entity::operator=(const Entity& other)
    {
        if (this==&other)
            return *this;
        m_pos = other.m_pos;
        m_cornerBR = other.m_cornerBR;
        m_cornerUL = other.m_cornerUL;
        m_type = other.m_type;
        return *this;
    }

    /**
     * Move constructor of Entity.
     * @param other Entity to move.
     */
    Entity::Entity(Entity&& other) noexcept
            :m_pos(other.m_pos), m_cornerUL(other.m_cornerUL), m_cornerBR(other.m_cornerBR),
             m_colliders(other.m_colliders), m_type(other.m_type)
    {
        other.m_colliders.clear();
    }

    /**
     * Move assignment operator.
     * @param other Entity to move.
     * @return Reference to entity which is equal to the original other.
     */
    Entity& Entity::operator=(Entity&& other) noexcept
    {
        if (this==&other)
            return *this;
        m_pos = other.m_pos;
        m_cornerBR = other.m_cornerBR;
        m_cornerUL = other.m_cornerUL;
        m_colliders = other.m_colliders;
        m_type = other.m_type;
        other.m_colliders.clear();
        return *this;
    }

    /**
     * Checks whether the Entity is in the coordinate system of the game logic.
     * @return True if the position is in [-4,4] x [-3,3].
     */
    bool Entity::isVisible() const
    {
        auto trans = Transformation::getInstance();
        range xRange = trans->getXRange();
        range yRange = trans->getYRange();
        return !(m_pos.x<xRange.first || m_pos.x>xRange.second || m_pos.y<yRange.first || m_pos.y>yRange.second);
    }

    /**
     * Getter for Position of entity.
     * @return Const reference to entity position.
     */
    const Position& Entity::getPos() const
    {
        return m_pos;
    }

    /**
     * Setter for Position of Entity.
     * @param pos New position for Entity.
     */
    void Entity::setPos(const Position& pos)
    {
        Entity::m_pos = pos;
    }

    /**
     * Getter for upper left corner of the Entity.
     * @return Const reference to Position of the upper left corner.
     */
    const Position& Entity::getUpperLeftCorner() const
    {
        return m_cornerUL;
    }

    /**
     * Getter for the bottom right corner of the Entity.
     * @return Const reference to Position of bottom right corner.
     */
    const Position& Entity::getBottomRightCorner() const
    {
        return m_cornerBR;
    }

    /**
     * Setter for upper left corner of Entity.
     * @param cornerUpLeft New Position of upper left corner.
     */
    void Entity::setUpperLeftCorner(const Position& cornerUpLeft)
    {
        Entity::m_cornerUL = cornerUpLeft;
    }

    /**
     * Setter for bottom right corner of Entity.
     * @param cornerBottomRight New Position of bottom right corner.
     */
    void Entity::setBottomRightCorner(const Position& cornerBottomRight)
    {
        Entity::m_cornerBR = cornerBottomRight;
    }

    /**
     * Calculates the width of the Entity based on the two corners.
     * @return Width of Entity.
     */
    double Entity::getWidth() const
    {
        return fabs(m_cornerUL.x-m_cornerBR.x);
    }

    /**
     * Calculates the height of the Entity based on the two corners.
     * @return Height of the Entity.
     */
    double Entity::getHeight() const
    {
        return fabs(m_cornerUL.y-m_cornerBR.y);
    }

    /**
     * Setter for position of Entity.
     * @param x X value of Position of Entity.
     * @param y Y value of Position of Entity.
     */
    void Entity::setPos(double x, double y)
    {
        double dx = x-m_pos.x;
        double dy = y-m_pos.y;
        m_pos.x = x;
        m_pos.y = y;
        m_cornerBR.x += dx;
        m_cornerBR.y += dy;
        m_cornerUL.x += dx;
        m_cornerUL.y += dy;
        for(BoxCollider& collider : m_colliders){
            collider.updateCollider(dx, dy);
        }
    }

    /**
     * Updates the position of the entity.
     * This function also updates the two corners respectively.
     * @param x X value to add to the Position.
     * @param y Y value to add to the Position.
     */
    void Entity::updatePos(double x, double y)
    {
        m_pos.x += x;
        m_pos.y += y;
        m_cornerUL.x += x;
        m_cornerUL.y += y;
        m_cornerBR.x += x;
        m_cornerBR.y += y;
        for(auto& collider : m_colliders)
            collider.updateCollider(x, y);
    }

    /**
     * Adds a collider to the Entity.
     * @param collider Collider to add to the entity.
     */
    void Entity::addCollider(const BoxCollider& collider)
    {
        m_colliders.push_back(collider);
    }

    /**
     * Removes a collider form the Entity.
     * @param i Index of collider to remove.
     */
    void Entity::removeCollider(int i)
    {
        m_colliders.erase(m_colliders.begin()+i);
    }

    /**
     * Getter for colliders.
     * @return Vector of box colliders.
     */
    const vector<BoxCollider>& Entity::getColliders() const
    {
        return m_colliders;
    }

    /**
     * Initializes the upper left and the bottom right corner.
     * This function also adds a collider to the entity.
     * Make sure the position is (0,0) when this function gets called.
     * If there is another position, it will be reset to (0,0).
     * @param width Width of the entity.
     * @param height Height of the entity.
     */
    void Entity::initializeCorners(double width, double height)
    {
        setPos(0,0);
        setUpperLeftCorner({-width/2, height/2});
        setBottomRightCorner({width/2,-height/2});
        BoxCollider collider(getUpperLeftCorner(), getBottomRightCorner());
        addCollider(collider);
    }

    /**
     * Getter for the type of the Entity.
     * @return Type of the entity.
     */
    EntityType Entity::getType() const
    {
        return m_type;
    }

    /**
     * Setter for the type of the Entity.
     * @param type Type of the entity.
     */
    void Entity::setType(const EntityType& type)
    {
        m_type = type;
    }

    /**
     * Disable all the colliders of the entity.
     */
    void Entity::disableColliders()
    {
        for(auto& collider : m_colliders)
            collider.disable();
    }

} // namespace RoadFighter
