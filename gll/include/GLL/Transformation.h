#ifndef ROADFIGHTER_TRANSFORMATION_H
#define ROADFIGHTER_TRANSFORMATION_H

#include <memory>
#include <GLL/Position.h>

using namespace std;
using range = pair<double, double>;

namespace RoadFighter {

    /**
     * Class used to do all Transformation related functions.
     * This class is based on the Singleton design pattern.
     * The Transformation class holds:
     * - a static instance of itself (Singleton).
     * - the height of the window.
     * - the width of the window.
     * - the ranges of the game logic (default [-4,4]x[-3,3]).
     */
    class Transformation {
    private:
        static shared_ptr<Transformation> m_instance;

        /**
         * Default private (!) constructor (Singleton pattern).
         */
        Transformation();

        unsigned int m_windowWidth;
        unsigned int m_windowHeight;

        // Variables which represent the coordinate system of the game
        range m_rangeX;
        range m_rangeY;
    public:
        /**
         * Default destructor
         */
        virtual ~Transformation();

        /**
         * Getter for the instance of the class.
         * If there is no instance yet, it will be created.
         * @return Static instance of the class as a shared pointer.
         */
        static shared_ptr<Transformation> getInstance();

        /**
         * Sets the sizes of the window.
         * @param width Width of the window.
         * @param height Height of the window.
         */
        void setScreenSize(unsigned int width, unsigned int height);

        /**
         * Sets the range on the x-axis.
         * If from is bigger than to, the values are swapped.
         * @param from Minimum of the range.
         * @param to Maximum of the range.
         */
        void setRangeX(double from, double to);

        /**
         * Sets the range on the y-axis.
         * If from is bigger than to, the values are swapped.
         * @param from Minimum of the range.
         * @param to Maximum of the range.
         */
        void setRangeY(double from, double to);

        /**
         * Calculates the coordinate on the window.
         * @param cartesianX X value of coordinate in game logic.
         * @param cartesianY Y value of coordinate in game logic.
         * @return Position on the screen (screen coordinate).
         */
        Position getScreenCoordinate(double cartesianX, double cartesianY);

        /**
         * Calculates the coordinate on the window.
         * @param cartesianPos Coordinate in game logic.
         * @return Position on the screen (screen coordinate).
         */
        Position getScreenCoordinate(const Position& cartesianPos);

        /**
         * Getter for the range of x-axis.
         * @return A pair of doubles representing the range on the x-axis.
         */
        const range& getXRange() const;

        /**
         * Getter for the range of y-axis.
         * @return A pair of doubles representing the range on the y-axis.
         */
        const range& getYRange() const;

        /**
         * Determine whether a position is in the grid or not.
         * @param pos Position which needs to be checked.
         * @return True if the position is in the grid.
         */
        bool isInGrid(const Position& pos);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_TRANSFORMATION_H
