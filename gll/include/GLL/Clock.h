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
    public:
        /**
         * Default constructor for Clock
         * This constructor will start the time
         */
        Clock();

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
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_CLOCK_H
