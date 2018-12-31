#ifndef ROADFIGHTER_CLOCK_H
#define ROADFIGHTER_CLOCK_H

#include <ctime>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents a clock.
     * A clock has:
     * - Start time.
     * - An amount of milliseconds to wait (when timer is used).
     * - A bool to check whether the timer is running.
     */
    class Clock {
    private:
        clock_t m_start;
        int m_msToWait;
        bool m_timerRunning;
    public:
        /**
         * Default constructor for Clock.
         * This constructor will start the time.
         */
        Clock();

        explicit Clock(int ms_to_wait);

        /**
         * Calculates the elapsed time and returns it as seconds.
         * @return Elapsed time in seconds.
         */
        double getTimeAsSeconds() const;

        /**
         * Calculates the elapsed time and returns it as milliseconds.
         * @return Elapsed time in milliseconds.
         */
        double getTimeAsMilliseconds() const;

        /**
         * Resets the clock.
         * Also resets the timer.
         */
        void reset();

        /**
         * Starts the timer.
         */
        void startTimer();

        /**
         * Check whether the timer has finished.
         * @return True if the timer has finished.
         */
        bool timerFinished();

        /**
         * Sets the timer.
         * @param ms_to_wait Amount of milliseconds to time.
         */
        void setTimer(int ms_to_wait);

        /**
         * Returns remaining time of timer.
         * @return Remaining time (in milliseconds).
         */
        int timeRemaining() const;

        /**
         * Returns remaining time of timer.
         * @return Remaining time (in seconds).
         */
        int timeRemainingAsSeconds() const;

        /**
         * Check whether the timer is running.
         * @return True if the timer is running.
         */
        bool timerRunning() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_CLOCK_H
