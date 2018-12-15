#ifndef ROADFIGHTER_OBSERVER_H
#define ROADFIGHTER_OBSERVER_H

#include <memory>
#include "Position.h"

using namespace std;

namespace RoadFighter {

    class Player; // forward declaration to avoid circular linking: Player includes observer and vice versa

    /**
     * Abstract observer class
     * See Observer design pattern for details
     */
    class Observer {
    protected:
        double m_textLength = 0;
    public:
        /**
         * Default constructor of Observer
         */
        Observer() = default;

        /**
         * Default destructor of Observer
         */
        virtual ~Observer() = default;

        /**
         * Pure virtual update function which is implemented in all derived classes
         */
        virtual void update() = 0;

        /**
         * Pure virtual draw function which needs to be implemented in derived classes
         */
        virtual void draw() const = 0;
    };

    /**
     * Observer for the speed of the Player
     * This observer has:
     * - A subject (in this case a shared ptr to a Player)
     * - A string which contains some additional information ex. 'speed: '
     * - A position:: the position where to display the result
     */
    class SpeedObserver : public Observer {
    protected:
        shared_ptr<Player> m_subject;
        string m_string;
        Position m_pos;
    public:
        /**
         * Constructor for SpeedObserver
         * @param subject Subject to observe
         * @param str String containing additional information ex. 'speed: '
         */
        SpeedObserver(const shared_ptr<Player>& subject, const string& str);

        /**
         * Update the speed observer with the new speed of the subject
         */
        void update() override;

        /**
         * Get the player speed in a 'realistic' form
         * @return Speed in a 'realistic' form (multiplied by 10)
         */
        unsigned int getPlayerSpeed() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_OBSERVER_H
