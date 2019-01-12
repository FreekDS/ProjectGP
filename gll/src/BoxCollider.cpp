#include <GLL/BoxCollider.h>

namespace RoadFighter {

    /**
     * Constructor for a box collider.
     * The constructor will reformat the corners if corner1 is not the upper left corner
     * and corner two is not the bottom right corner, so they match the requirements for this collider.
     * @param corner1 First corner of the collision rectangle
     * @param corner2 Second corner of the collision rectangle
     */
    BoxCollider::BoxCollider(Position cornerUL, Position cornerBR)
    {
        if (cornerUL.x==cornerBR.x || cornerUL.y==cornerBR.y)
            throw invalid_argument(
                    "Cannot create box collider with corners "+cornerUL.toString()+" and "+cornerBR.toString());
        m_br = cornerBR;
        m_ul = cornerUL;
    }

    /**
     * Getter for upper left corner.
     * @return Upper left corner.
     */
    const Position& BoxCollider::getUpperLeftCorner() const
    {
        return m_ul;
    }

    /**
     * Getter for bottom right corner.
     * @return Bottom right corner..
     */
    const Position& BoxCollider::getBottomRightCorner() const
    {
        return m_br;
    }

    /**
     * Default destructor for BoxCollider.
     */
    BoxCollider::~BoxCollider() = default;

    /**
     * Updates the corners of the collider.
     * @param x X value to add to collider.
     * @param y Y value to add to collider.
     */
    void BoxCollider::updateCollider(double x, double y)
    {
        m_br.x += x;
        m_br.y += y;
        m_ul.x += x;
        m_ul.y += y;
    }

    /**
     * Calculates the center of the box and return it.
     * @return Position of center of the box collider.
     */
    Position BoxCollider::getCenter() const
    {
        double x = (m_ul.x+m_br.x)/2.0;
        double y = (m_br.y+m_ul.y)/2.0;
        return Position(x, y);
    }

    /**
     * Equality operator for BoxCollider.
     * @param rhs Other collider.
     * @return True if this equals the other the collider.
     */
    bool BoxCollider::operator==(const BoxCollider& rhs) const
    {
        return m_ul==rhs.m_ul &&
                m_br==rhs.m_br;
    }

    /**
     * Inequality operator for BoxCollider.
     * @param rhs Other collider.
     * @return True if this equals the other the collider.
     */
    bool BoxCollider::operator!=(const BoxCollider& rhs) const
    {
        return !(rhs==*this);
    }

} // namespace RoadFighter
