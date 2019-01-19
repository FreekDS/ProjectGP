#ifndef ROADFIGHTER_OBSERVER_H
#define ROADFIGHTER_OBSERVER_H

#include <memory>
#include "Position.h"
#include "Clock.h"

using namespace std;

namespace RoadFighter {

    class Player; // forward declaration to avoid circular linking: Player includes observer and vice versa.

    /**
     * Enum to determine the different types of observer.
     */
    enum ObserverType {
        UNDECLARED,
        SPEED,
        DISTANCE,
        SCORE
    };

    /**
     * Observer interface class.
     * See Observer design pattern for details.
     */
    class Observer {
    public:
        /**
         * Default constructor of Observer.
         */
        Observer() = default;

        /**
         * Default destructor of Observer.
         */
        virtual ~Observer() = default;

        /**
         * Pure virtual update function which is implemented in all derived classes.
         */
        virtual void update() = 0;

        /**
         * Pure virtual draw function which needs to be implemented in derived classes.
         */
        virtual void draw() const = 0;

        /**
         * Gets the type of the observer.
         * @return UNKNOWN observer.
         */
        virtual ObserverType getType() const
        {
            return ObserverType::UNDECLARED;
        }
    };

    /**
     * Observer for the speed of the Player.
     * This observer has:
     * - A subject (in this case a shared ptr to a Player).
     * - A string which contains some additional information ex. 'speed: '.
     * - A position:: the position where to display the result.
     */
    class SpeedObserver : public Observer {
    protected:
        shared_ptr<Player> m_subject;
        string m_string;
        Position m_pos;
    public:
        /**
         * Constructor for SpeedObserver.
         * @param subject Subject to observe.
         * @param str String containing additional information ex. 'speed: '.
         */
        SpeedObserver(const shared_ptr<Player>& subject, const string& str);

        /**
         * Update the speed observer with the new speed of the subject.
         */
        void update() override;

        /**
         * Get the player speed in a 'realistic' form.
         * @return Speed in a 'realistic' form (multiplied by 10).
         */
        unsigned int getPlayerSpeed() const;

        /**
         * Gets the type of the observer.
         * @return SPEED observer.
         */
        ObserverType getType() const override;
    };

    /**
     * This class is derived of Observer and has:
     * - a shared pointer to the subject
     * - a double containing the covered distance
     * - a constant integer containing the update rate
     * - a clock
     */
    class DistanceObserver : public Observer {
    private:
        shared_ptr<Player> m_subject;
        double m_coveredDistance;
        const int m_updateTick;
        Clock m_clock;
    public:
        /**
         * Constructor for Distance observer.
         * @param subject Subject to observe.
         */
        explicit DistanceObserver(const shared_ptr<Player>& subject);

        /**
         * Update the covered distance.
         */
        void update() override;

        /**
         * Draws the observer. Does nothing as this observer does not need to be drawn.
         */
        void draw() const override { }

        /**
         * Gets the type of the observer.
         * @return DISTANCE observer.
         */
        ObserverType getType() const override;
    };

    /**
     * This class is derived of Observer and has
     * - a shared pointer to the subject
     * - an int containing the last known distance
     * - an unsigned integer containing the score of the observer
     * - a string containing the message to display ex. "Score: "
     * - the position of the drawable text
     */
    class ScoreObserver : public Observer {
    protected:
        shared_ptr<Player> m_subject;
        int m_lastDistance;
        int m_score;
        std::string m_string;
        Position m_pos;
    public:
        /**
         * Constructor for the score observer.
         * @param subject Subject to observe.
         * @param msg Message to display ex. "Score: "
         */
        ScoreObserver(const shared_ptr<Player>& subject, const std::string& msg);

        /**
         * Updates the score observer.
         * Also calls @see updateDrawable()
         */
        void update() override;

        /**
         * Returns the type of the observer
         * @return ObserverType::SCORE
         */
        ObserverType getType() const override;

        /**
         * Returns the score of the observer.
         * @return Score of the observer
         */
        unsigned int getScore() const;

        /**
         * Updates the score of the observer with a certain amount. (may be positive or negative)
         * @param score Score to update score with.
         */
        void updateScore(int score);

        /**
         * Updates the drawable text of the observer.
         */
        virtual void updateDrawable() = 0;

    };

} // namespace RoadFighter

#endif //ROADFIGHTER_OBSERVER_H
