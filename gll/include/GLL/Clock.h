#ifndef ROADFIGHTER_CLOCK_H
#define ROADFIGHTER_CLOCK_H

#include <ctime>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents a clock
     * A clock has:
     * - start time
     */
    class Clock {
    private:
        clock_t m_start;
        int m_msToWait;
        bool m_timerRunning;
    public:
        /**
         * Default constructor for Clock
         * This constructor will start the time
         */
        Clock();

        explicit Clock(int ms_to_wait);

        /**
         * Calculates the elapsed time and returns it as seconds
         * @return Elapsed time in seconds
         */
        double getTimeAsSeconds() const;

        /**
         * Calculates the elapsed time and returns it as milliseconds
         * @return Elapsed time in milliseconds
         */
        double getTimeAsMilliseconds() const;

        /**
         * Resets the clock
         */
        void reset();

        void startTimer();

        bool timerFinished();

        void setTimer(int ms_to_wait);

        int timeRemaining() const;

        int timeRemainingAsSeconds() const;

        bool timerRunning() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_CLOCK_H
