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

    class ScoreObserver : public Observer {
    protected:
        shared_ptr<Player> m_subject;
        double m_lastDistance;
        unsigned int m_score;
        std::string m_string;
        Position m_pos;
    public:
        ScoreObserver(const shared_ptr<Player>& subject, const std::string& msg);

        void update() override;

        ObserverType getType() const override;

        unsigned int getScore() const;

        void updateScore(int score);

        virtual void updateDrawable() = 0;

    };

} // namespace RoadFighter

#endif //ROADFIGHTER_OBSERVER_H
