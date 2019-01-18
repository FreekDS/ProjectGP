#include <GLL/Transformation.h>

namespace RoadFighter {

    // instance needs to be initialized to prevent linker errors
    shared_ptr<Transformation> Transformation::m_instance = nullptr;

    /**
     * Default private (!) constructor (Singleton pattern)
     */
    Transformation::Transformation()
            :m_windowWidth(0),
             m_windowHeight(0),
             m_rangeX({-4, 4}),
             m_rangeY({-3, 3}) { }


    /**
     * Getter for the instance of the class.
     * If there is no instance yet, it will be created.
     * @return Static instance of the class as a shared pointer.
     */
    shared_ptr<RoadFighter::Transformation> Transformation::getInstance()
    {
        if (m_instance==nullptr)
            m_instance = shared_ptr<Transformation>(new Transformation);
        return m_instance;
    }

    /**
     * Sets the sizes of the window.
     * @param width Width of the window.
     * @param height Height of the window.
     */
    void Transformation::setScreenSize(unsigned int width, unsigned int height)
    {
        m_windowWidth = width;
        m_windowHeight = height;
    }

    /**
      * Sets the range on the x-axis.
      * If from is bigger than to, the values are swapped.
      * @param from Minimum of the range.
      * @param to Maximum of the range.
      */
    void Transformation::setRangeX(double from, double to)
    {
        if (from>to)
            swap(from, to);
        m_rangeX.first = from;
        m_rangeX.second = to;
    }

    /**
     * Sets the range on the y-axis.
     * If from is bigger than to, the values are swapped.
     * @param from Minimum of the range.
     * @param to Maximum of the range.
     */
    void Transformation::setRangeY(double from, double to)
    {
        if (from>to)
            swap(from, to);
        m_rangeY.first = from;
        m_rangeY.second = to;
    }

    /**
     * Calculates the coordinate on the window.
     * @param cartesianX X value of coordinate in game logic.
     * @param cartesianY Y value of coordinate in game logic.
     * @return Position on the screen (screen coordinate).
     */
    Position Transformation::getScreenCoordinate(double cartesianX, double cartesianY)
    {
        Position screenPos;
        double lengthX = m_rangeX.second-m_rangeX.first;
        double lengthY = m_rangeY.second-m_rangeY.first;
        screenPos.x = (cartesianX+lengthX/2)*1/lengthX*m_windowWidth;
        screenPos.y = (cartesianY-lengthY/2)*-1/lengthY*m_windowHeight;
        return screenPos;
    }

    /**
     * Getter for the range of x-axis.
     * @return A pair of doubles representing the range on the x-axis.
     */
    const range& Transformation::getXRange() const
    {
        return m_rangeX;
    }

    /**
     * Getter for the range of y-axis.
     * @return A pair of doubles representing the range on the y-axis.
     */
    const range& Transformation::getYRange() const
    {
        return m_rangeY;
    }

    /**
     * Calculates the coordinate on the window.
     * @param cartesianPos Coordinate in game logic.
     * @return Position on the screen (screen coordinate).
     */
    Position Transformation::getScreenCoordinate(const Position& cartesianPos)
    {
        Position screenPos;
        double lengthX = m_rangeX.second-m_rangeX.first;
        double lengthY = m_rangeY.second-m_rangeY.first;
        screenPos.x = (cartesianPos.x+lengthX/2)*1/lengthX*m_windowWidth;
        screenPos.y = (cartesianPos.y-lengthY/2)*-1/lengthY*m_windowHeight;
        return screenPos;
    }

    /**
     * Determine whether a position is in the grid or not.
     * @param pos Position which needs to be checked.
     * @return True if the position is in the grid.
     */
    bool Transformation::isInGrid(const Position& pos)
    {
        bool checkX = pos.x>=m_rangeX.first && pos.x<=m_rangeX.second;
        bool checkY = pos.y>=m_rangeY.first && pos.y<=m_rangeY.second;
        return checkX && checkY;
    }

    unsigned int Transformation::getWindowWidth() const
    {
        return m_windowWidth;
    }

    unsigned int Transformation::getWindowHeight() const
    {
        return m_windowHeight;
    }

    /**
     * Default destructor
     */
    Transformation::~Transformation() = default;

} // namespace RoadFighter