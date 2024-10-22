#ifndef ROADFIGHTER_RANDOM_H
#define ROADFIGHTER_RANDOM_H

#include <memory>
#include <random>

namespace RoadFighter {

    /**
     * Class used to generate random numbers.
     * This class is based on the Singleton design pattern.
     * This class has:
     * - A generator.
     * - An instance of itself (singleton).
     */
    class Random {
    private:
        std::mt19937 m_randomNumberGenerator;
        static std::shared_ptr<Random> m_instance;

        /**
         * Private constructor for Random class.
         * Used to generate the only instance of this class.
         * Creates a random number generator seeded with the time.
         */
        Random();

    public:

        /**
         * Delete the copy constructor to make sure there can only be one instance of this class.
         */
        Random(Random const&) = delete;

        /**
         * Delete the assignment operator to make sure there can only be one instance of this class.
         */
        Random& operator=(Random const&) = delete;

        /**
         * Destructor for Random class.
         */
        virtual ~Random();

        /**
         * Gets the static instance of this class.
         * If there is no static instance, this function creates one.
         * @return Static instance of Random.
         */
        static std::shared_ptr<Random> getInstance();

        /**
         * Generates a random integer between two values.
         * If min > max, the values are swapped.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random number between min and max.
         */
        int randInt(unsigned int min, unsigned int max);

        /**
         * Generates a random double between two values.
         * If min > max, the values are swapped.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random double between min and max.
         */
        double randDouble(double min, double max);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_RANDOM_H
