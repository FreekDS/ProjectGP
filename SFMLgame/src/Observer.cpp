#include <GLL/Transformation.h>
#include <Observer.h>

namespace RoadFighterSFML {

    /**
     * Constructor for SpeedObserver
     * This constructor initializes the font on the font ./res/font/font.ttf
     * The SFML text is initialized with the string of the base class + 0
     * The position of the text is determined by converting m_pos to screen coordinates
     * @param subject Subject to observe (Player)
     * @param str String with additional information ex. 'Speed: '
     * @param window Window to draw results to
     */
    SpeedObserver::SpeedObserver(const shared_ptr<RoadFighter::Player>& subject, const string& str,
            const window_ptr& window) : RoadFighter::SpeedObserver(subject, str), m_window(window)
    {
        m_font.loadFromFile("./res/font/font.ttf");
        m_text.setFont(m_font);
        m_text.setString(str + "0");
        m_text.scale(0.7, 0.7);
        auto trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(m_pos);
        m_text.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }


    void SpeedObserver::update()
    {
        string speed = to_string(m_subject->getSpeed());
        m_text.setString(m_string + speed);
        m_window->draw(m_text);
    }

    void SpeedObserver::draw() const
    {
        m_window->draw(m_text);
    }

} // namespace RoadFighterSFML

