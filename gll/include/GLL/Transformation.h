#ifndef ROADFIGHTER_TRANSFORMATION_H
#define ROADFIGHTER_TRANSFORMATION_H

#include <memory>
#include <GLL/Position.h>

using namespace std;
using range = pair<double, double>;

namespace RoadFighter {

    class Transformation {
    private:
        static shared_ptr<Transformation> m_instance;

        Transformation();

        unsigned int m_windowWidth;
        unsigned int m_windowHeight;

        // Variables which represent the coordinate system of the game
        range m_rangeX;
        range m_rangeY;
    public:
        virtual ~Transformation();

        static shared_ptr<Transformation> getInstance();

        void setScreenSize(unsigned int width, unsigned int height);

        void setRangeX(double from, double to);

        void setRangeY(double from, double to);

        Position getScreenCoordinate(double cartesianX, double cartesianY);

        Position getScreenCoordinate(const Position& cartesianPos);

        range getXRange() const;

        range getYRange() const;

        bool isInGrid(const Position& pos);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_TRANSFORMATION_H
