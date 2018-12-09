#include <GLL/Transformation.h>

namespace RoadFighter {

    shared_ptr<Transformation> Transformation::m_instance = nullptr;

    Transformation::Transformation()
            :m_windowWidth(0),
             m_windowHeight(0),
             m_rangeX({-4, 4}),
             m_rangeY({-3, 3}) { }

    shared_ptr<RoadFighter::Transformation> Transformation::getInstance()
    {
        if (m_instance==nullptr)
            m_instance = shared_ptr<Transformation>(new Transformation);
        return m_instance;
    }

    void Transformation::setScreenSize(unsigned int width, unsigned int height)
    {
        m_windowWidth = width;
        m_windowHeight = height;
    }

    void Transformation::setRangeX(double from, double to)
    {
        if (from>to)
            swap(from, to);
        m_rangeX.first = from;
        m_rangeX.second = to;
    }

    void Transformation::setRangeY(double from, double to)
    {
        if (from>to)
            swap(from, to);
        m_rangeY.first = from;
        m_rangeY.second = to;
    }

    Position Transformation::getScreenCoordinate(double cartesianX, double cartesianY)
    {
        Position screenPos;
        double lengthX = m_rangeX.second-m_rangeX.first;
        double lengthY = m_rangeY.second-m_rangeY.first;
        screenPos.x = (cartesianX+lengthX/2)*1/lengthX*m_windowWidth;
        screenPos.y = (cartesianY-lengthY/2)*-1/lengthY*m_windowHeight;
        return screenPos;
    }

    range Transformation::getXRange() const
    {
        return m_rangeX;
    }

    range Transformation::getYRange() const
    {
        return m_rangeY;
    }

    Position Transformation::getScreenCoordinate(const Position& cartesianPos)
    {
        Position screenPos;
        double lengthX = m_rangeX.second-m_rangeX.first;
        double lengthY = m_rangeY.second-m_rangeY.first;
        screenPos.x = (cartesianPos.x+lengthX/2)*1/lengthX*m_windowWidth;
        screenPos.y = (cartesianPos.y-lengthY/2)*-1/lengthY*m_windowHeight;
        return screenPos;
    }

    bool Transformation::isInGrid(const Position& pos)
    {
        bool checkX = pos.x >= m_rangeX.first && pos.x <= m_rangeX.second;
        bool checkY = pos.y >= m_rangeY.first && pos.y <= m_rangeY.second;
        return checkX && checkY ;
    }

    Transformation::~Transformation() = default;

} // namespace RoadFighter