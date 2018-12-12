#ifndef ROADFIGHTER_COLLIDER_H
#define ROADFIGHTER_COLLIDER_H

#include "Position.h"
#include <vector>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents a 2D Collider
     * A Collider has:
     * - An upper left corner
     * - A bottom right corner
     */
    class BoxCollider {
    private:
        Position m_ul;
        Position m_br;
    public:
        /**
         * Constructor for a box collider
         * The constructor will reformat the corners if corner1 is not the upper left corner
         * and corner two is not the bottom right corner, so they match the requirements for this collider
         * @param corner1 First corner of the collision rectangle
         * @param corner2 Second corner of the collision rectangle
         * @throws invalid_argument if x1 == x2 or y1 == y2
         */
        BoxCollider(Position corner1, Position corner2);

        /**
         * Getter for upper left corner
         * @return Upper left corner
         */
        const Position& getUpperLeftCorner() const;

        /**
         * Getter for bottom right corner
         * @return Bottom right corner
         */
        const Position& getBottomRightCorner() const;

        /**
         * Default destructor for BoxCollider
         */
        virtual ~BoxCollider();

        /**
         * Updates the corners of the collider
         * @param x X value to add to collider
         * @param y Y value to add to collider
         */
        void updateCollider(double x, double y);

        /**
         * Calculates the center of the box and return it
         * @return Position of center of the box collider
         */
        Position getCenter() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_COLLIDER_H
