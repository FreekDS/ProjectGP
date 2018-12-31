#include <GLL/Clock.h>
#include <stdexcept>
#include <cmath>

namespace RoadFighter {

    /**
     * Default constructor for Clock.
     * This constructor will start the time.
     */
    RoadFighter::Clock::Clock()
            :m_start(clock()) { }

    /**
     * Calculates the elapsed time and returns it as seconds.
     * @return Elapsed time in seconds.
     */
    double RoadFighter::Clock::getTimeAsSeconds() const
    {
        return static_cast<double>(clock()-m_start)/CLOCKS_PER_SEC;
    }

    /**
     * Calculates the elapsed time and returns it as milliseconds.
     * @return Elapsed time in milliseconds.
     */
    double RoadFighter::Clock::getTimeAsMilliseconds() const
    {
        return getTimeAsSeconds()*1000;
    }

    /**
     * Resets the clock.
     * Also resets the timer.
     */
    void RoadFighter::Clock::reset()
    {
        m_start = clock();
        m_timerRunning = false;
    }

    Clock::Clock(int ms_to_wait) : m_start(clock()), m_msToWait(ms_to_wait), m_timerRunning(false)
    {}

    /**
     * Starts the timer.
     */
    void Clock::startTimer()
    {
        reset();
        m_timerRunning = true;
    }

    /**
     * Check whether the timer has finished.
     * @return True if the timer has finished.
     */
    bool Clock::timerFinished()
    {
        if(getTimeAsMilliseconds() >= m_msToWait) {
            m_start = clock();
            return true;
        }
        return false;
    }

    /**
     * Sets the timer.
     * @param ms_to_wait Amount of milliseconds to time.
     */
    void Clock::setTimer(int ms_to_wait)
    {
        m_msToWait = ms_to_wait;
    }

    /**
     * Returns remaining time of timer.
     * @return Remaining time (in milliseconds).
     */
    int Clock::timeRemaining() const
    {
        if(m_timerRunning)
            return m_msToWait - static_cast<int>(round(getTimeAsMilliseconds()));
        else
            throw std::runtime_error("Timer is not running...");
    }

    /**
     * Returns remaining time of timer.
     * @return Remaining time (in seconds).
     */
    int Clock::timeRemainingAsSeconds() const
    {
        return static_cast<int>(round(timeRemaining() / 1000));
    }

    /**
     * Check whether the timer is running.
     * @return True if the timer is running.
     */
    bool Clock::timerRunning() const
    {
        return m_timerRunning;
    }

} // namespace RoadFighter
