#include <GLL/Transformation.h>
#include <Observer.h>
#include <iostream>

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
        m_text.setString(str);
        m_text.setFillColor(sf::Color::White);
        m_value.setFont(m_font);
        m_value.setString("0");
        m_value.setFillColor(sf::Color::Green);

        m_text.scale(0.7, 0.7);
        m_value.scale(0.7, 0.7);

        auto trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(m_pos);
        m_text.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
        m_value.setPosition(m_text.getPosition().x + m_text.getGlobalBounds().width, m_text.getPosition().y);
    }

    /**
     * Updates the SpeedObserver
     * - Changes SFML text to string of base class + speed of subject
     * - Draws the text to the screen
     */
    void SpeedObserver::update()
    {
        updateTextColor();
        m_value.setString(to_string(getPlayerSpeed()) + " km/h");
    }

    /**
     * Draws the observer to the window
     */
    void SpeedObserver::draw() const
    {
        m_window->draw(m_text);
        m_window->draw(m_value);
    }

    /**
     * Updates the text color based on the speed of the player
     */
    void SpeedObserver::updateTextColor()
    {
        if(m_subject->getSpeed() < m_subject->getMaxSpeed()/2)
            m_value.setFillColor(sf::Color::Green);
        if(m_subject-> getSpeed() > m_subject->getMaxSpeed()/2
            && m_subject->getSpeed() < m_subject->getMaxSpeed()* 8/10)
            m_value.setFillColor(sf::Color(253, 106, 2));
        if(m_subject->getSpeed() > m_subject->getMaxSpeed()* 8/10)
            m_value.setFillColor(sf::Color::Red);
    }

} // namespace RoadFighterSFML

