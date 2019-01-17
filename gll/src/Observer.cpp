#include <GLL/Observer.h>
#include <GLL/Player.h>
#include <iostream>
#include <cmath>

namespace RoadFighter {

//Speed observer /////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor for SpeedObserver.
     * @param subject Subject to observe
     * @param str String containing additional information ex. 'speed: '.
     */
    SpeedObserver::SpeedObserver(const shared_ptr<Player>& subject, const string& str)
            :m_subject(subject), m_string(str), m_pos(1.7, 2.5)
    {

    }

    /**
     * Update the speed observer with the new speed of the subject.
     */
    void SpeedObserver::update()
    {
        cout << m_string << ": " << getPlayerSpeed() << endl;
    }

    /**
     * Get the player speed in a 'realistic' form.
     * @return Speed in a 'realistic' form (multiplied by 10).
     */
    unsigned int SpeedObserver::getPlayerSpeed() const
    {
        return static_cast<unsigned int>(round(m_subject->getSpeed()*10));
    }

    /**
     * Gets the type of the observer.
     * @return SPEED observer.
     */
    ObserverType SpeedObserver::getType() const
    {
        return ObserverType::SPEED;
    }


//Distance observer //////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor for Distance observer.
     * @param subject Subject to observe.
     */
    DistanceObserver::DistanceObserver(const shared_ptr<Player>& subject)
            :m_subject(subject), m_updateTick(500) { }

    /**
     * Update the covered distance.
     */
    void DistanceObserver::update()
    {
        if (m_clock.getTimeAsMilliseconds()>=m_updateTick) {
            m_clock.reset();
            if (m_subject->isMoving()) {
                m_coveredDistance += (m_subject->getSpeed()*m_updateTick)/1000;
                m_subject->setDistanceCovered(m_coveredDistance);
            }
        }
    }

    /**
     * Gets the type of the observer.
     * @return DISTANCE observer.
     */
    ObserverType DistanceObserver::getType() const
    {
        return ObserverType::DISTANCE;
    }

//Score observer //////////////////////////////////////////////////////////////////////////////////

    ScoreObserver::ScoreObserver(const shared_ptr<Player>& subject, const std::string& msg)
            :m_subject(subject), m_lastDistance(subject->getCoveredDistance()), m_score(0), m_string(msg), m_pos(1.7, 2)
    {

    }

    void ScoreObserver::update()
    {
        int distance = static_cast<int>(round(m_subject->getCoveredDistance()));
        if(distance > m_lastDistance){
            m_lastDistance = distance;
            m_score += distance;
        }
        updateDrawable();
    }

    ObserverType ScoreObserver::getType() const
    {
        return ObserverType::SCORE;
    }

    unsigned int ScoreObserver::getScore() const
    {
        return m_score;
    }

    void ScoreObserver::updateScore(int score)
    {
        m_score += score;
        updateDrawable();
    }
} // namespace RoadFighter