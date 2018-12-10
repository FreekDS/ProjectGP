#include <GLL/BoxCollider.h>

namespace RoadFighter {

    /**
     * Constructor for a box collider
     * The constructor will reformat the corners if corner1 is not the upper left corner
     * and corner two is not the bottom right corner, so they match the requirements for this collider
     * @param corner1 First corner of the collision rectangle
     * @param corner2 Second corner of the collision rectangle
     */
    BoxCollider::BoxCollider(Position cornerUL, Position cornerBR)
    {
        if (cornerUL.x>cornerBR.x)
            std::swap(cornerUL.x, cornerBR.x);
        if (cornerUL.y<cornerBR.y)
            std::swap(cornerBR.y, cornerUL.y);
        if (cornerUL.x==cornerBR.x || cornerUL.y==cornerBR.y)
            throw invalid_argument(
                    "Cannot create box collider with corners "+cornerUL.toString()+" and "+cornerBR.toString()
                            +"\nMake sure you give up the upper left and the bottom right corner");
        m_br = cornerBR;
        m_ul = cornerUL;
    }

    /**
     * Getter for upper left corner
     * @return Upper left corner
     */
    const Position& BoxCollider::getUpperLeftCorner() const
    {
        return m_ul;
    }

    /**
     * Getter for bottom right corner
     * @return Bottom right corner
     */
    const Position& BoxCollider::getBottomRightCorner() const
    {
        return m_br;
    }

    BoxCollider::~BoxCollider() = default;


} // namespace RoadFighter
