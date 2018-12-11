#include "GLL/Clock.h"

namespace RoadFighter {

    /**
     * Default constructor for Clock
     * This constructor will start the time
     */
    RoadFighter::Clock::Clock()
            :m_start(clock()) { }

    /**
     * Calculates the elapsed time and returns it as seconds
     * @return Elapsed time in seconds
     */
    double RoadFighter::Clock::getTimeAsSeconds() const
    {
        return static_cast<double>(clock()-m_start)/CLOCKS_PER_SEC;
    }

    /**
     * Calculates the elapsed time and returns it as milliseconds
     * @return Elapsed time in milliseconds
     */
    double RoadFighter::Clock::getTimeAsMilliseconds() const
    {
        return getTimeAsSeconds()*1000;
    }

    /**
     * Resets the clock
     */
    void RoadFighter::Clock::reset()
    {
        m_start = clock();
    }

} // namespace RoadFighter
