#include <GLL/Observer.h>
#include <GLL/Player.h>
#include <iostream>

namespace RoadFighter {

//Speed observer /////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor for SpeedObserver
     * @param subject Subject to observe
     * @param str String containing additional information ex. 'speed: '
     */
    SpeedObserver::SpeedObserver(const shared_ptr<Player>& subject, const string& str)
            :m_subject(subject), m_string(str), m_pos(2,2.4) { }

    /**
     * Update the speed observer with the new speed of the subject
     */
    void SpeedObserver::update()
    {
        cout << "Speed: " << m_subject->getSpeed() << endl;
    }


} // namespace RoadFighter