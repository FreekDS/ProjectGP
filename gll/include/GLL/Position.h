#ifndef ROADFIGHTER_COORDINATE_H
#define ROADFIGHTER_COORDINATE_H

namespace RoadFighter {

/**
 * This structure represents a position in 2 dimensional space
 * A position has an x value and a y value
 */
    struct Position {
        double x;
        double y;

        /**
         * Constructor of Position
         * Initializes the position on (0,0)
         */
        Position();

        /**
         * Constructor of Position
         * Initializes the position on given (x, y) value
         * @param x X value of position
         * @param y Y value of position
         */
        Position(double x, double y);

        /**
         * Assignment operator of Position
         * @param other Assign 'this' to other
         * @return reference to 'this'
         */
        Position& operator=(Position const& other);

        /**
         * Default destructor of Position
         */
        virtual ~Position();
    };

}

#endif //ROADFIGHTER_COORDINATE_H
