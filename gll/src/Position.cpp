#include "GLL/Position.h"

namespace RoadFighter {

    /**
     * Constructor of Position
     * Initializes the position on (0,0)
     */
    Position::Position()
            :x(0), y(0) { }

    /**
     * Constructor of Position
     * Initializes the position on given (x, y) value
     * @param x X value of position
     * @param y Y value of position
     */
    Position::Position(double xPos, double yPos)
            :x(xPos), y(yPos) { }

    /**
     * Assignment operator of Position
     * @param other Assign 'this' to other
     * @return reference to 'this'
     */
    Position& Position::operator=(Position const& other)
    {
        if (this==&other)
            return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    /**
     * Outputs the position to a stream
     * @param os Stream to output to
     * @param position  Position to output to
     * @return Reference to updated stream
     */
    std::ostream& operator<<(std::ostream& os, const Position& position)
    {
        os << "x: " << position.x << " y: " << position.y;
        return os;
    }

    /**
     * Default destructor of Position
     */
    Position::~Position() = default;

} // namespace RoadFighter