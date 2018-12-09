#include "GLL/Random.h"
#include <iostream>
#include <ctime>

namespace RoadFighter {

    /**
     * Initialize m_instance to avoid linker errors
     */
    std::shared_ptr<Random> Random::m_instance = nullptr;

    /**
     * Private constructor for Random class.
     * Used to generate the only instance of this class.
     * Creates a random number generator seeded with the time.
     */
    Random::Random()
            :m_randomNumberGenerator(static_cast<unsigned int>(time(nullptr))) { }

    /**
     * Gets the static instance of this class.
     * If there is no static instance, this function creates one.
     * @return Static instance of Random
     */
    std::shared_ptr<Random> Random::getInstance()
    {
        if (m_instance==nullptr)
            m_instance = std::shared_ptr<Random>(new Random());
        return m_instance;
    }

    /**
     * Destructor for Random class
     */
    Random::~Random() = default;

    /**
     * Generates a random integer between two values
     * If min > max, the values are swapped.
     * @param min minimum value
     * @param max maximum value
     * @return random number between min and max
     */
    int Random::randNum(unsigned int min, unsigned int max)
    {
        // If min is lower than max, swap values
        if (max<min) {
            std::swap(max, min);
        }
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(this->m_randomNumberGenerator);
    }

} // namespace RoadFighter
