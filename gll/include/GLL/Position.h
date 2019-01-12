#ifndef ROADFIGHTER_COORDINATE_H
#define ROADFIGHTER_COORDINATE_H

#include <ostream>

namespace RoadFighter {

    /**
     * This structure represents a position in 2 dimensional space.
     * A position has an x value and a y value.
     */
    struct Position {
        double x;
        double y;

        /**
         * Constructor of Position
         * Initializes the position on (0,0).
         */
        Position();

        /**
         * Constructor of Position.
         * Initializes the position on given (x, y) value.
         * @param x X value of position.
         * @param y Y value of position.
         */
        Position(double x, double y);

        /**
         * Assignment operator of Position.
         * @param other Assign 'this' to other.
         * @return reference to 'this'.
         */
        Position& operator=(Position const& other);

        /**
         * Default destructor of Position.
         */
        virtual ~Position();

        /**
         * Outputs the position to a stream.
         * @param os Stream to output to.
         * @param position  Position to output to.
         * @return Reference to updated stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Position& position);

        /**
         * Converts a position to a string of the form (x,y).
         * @return String representing the position.
         */
        const std::string toString() const;

        /**
         * Equality operator for Position.
         * @param lhs Left side of equality.
         * @param rhs Right side of equality.
         * @return True if lhs == rhs.
         */
        friend bool operator==(const Position& lhs, const Position& rhs);

        /**
         * Inequality operator for Position.
         * @param lhs Left side of inequality.
         * @param rhs Right side of inequality.
         * @return True if lhs != rhs.
         */
        friend bool operator!=(const Position& lhs, const Position& rhs);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_COORDINATE_H
