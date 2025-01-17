#include <GLL/Transformation.h>
#include <Observer.h>
#include <iostream>

namespace RoadFighterSFML {

    /**
     * Constructor for SpeedObserver.
     * This constructor initializes the font with the font "./res/font/font.ttf".
     * The SFML text is initialized with the string of the base class + 0.
     * The position of the text is determined by converting m_pos to screen coordinates.
     * @param subject Subject to observe (Player).
     * @param str String with additional information ex. 'Speed: '.
     * @param window Window to draw results to.
     */
    SpeedObserver::SpeedObserver(const shared_ptr<RoadFighter::Player>& subject, const string& str,
            const window_ptr& window) : RoadFighter::SpeedObserver(subject, str), m_window(window)
    {
        m_font.loadFromFile("./res/font/font.ttf");
        m_text.setFont(m_font);
        m_text.setString(str);
        m_text.setColor(sf::Color::White);
        m_value.setFont(m_font);
        m_value.setString("0");
        m_value.setColor(sf::Color::Green);

        m_text.scale(0.7, 0.7);
        m_value.scale(0.7, 0.7);

        auto trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(m_pos);
        m_text.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
        m_value.setPosition(m_text.getPosition().x + m_text.getGlobalBounds().width, m_text.getPosition().y);
    }

    /**
     * Updates the SpeedObserver.
     * - Changes SFML text to string of base class + speed of subject.
     * - Draws the text to the screen.
     */
    void SpeedObserver::update()
    {
        updateTextColor();
        m_value.setString(to_string(getPlayerSpeed()) + " km/h");
    }

    /**
     * Draws the observer to the window.
     */
    void SpeedObserver::draw() const
    {
        m_window->draw(m_text);
        m_window->draw(m_value);
    }

    /**
     * Updates the text color based on the speed of the player.
     */
    void SpeedObserver::updateTextColor()
    {
        if(m_subject->getSpeed() < m_subject->getMaxSpeed()/2)
            m_value.setColor(sf::Color::Green);
        if(m_subject-> getSpeed() > m_subject->getMaxSpeed()/2
            && m_subject->getSpeed() < m_subject->getMaxSpeed()* 8/10)
            m_value.setColor(sf::Color(253, 106, 2));
        if(m_subject->getSpeed() > m_subject->getMaxSpeed()* 8/10)
            m_value.setColor(sf::Color::Red);
    }

//Distance observer //////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor for the ScoreObserver
     * @param subject Subject to observe
     * @param str String to display ex. "Score: "
     * @param window Shared pointer to the window
     */
    ScoreObserver::ScoreObserver(const shared_ptr<RoadFighter::Player>& subject, const string& str,
            const window_ptr& window) : RoadFighter::ScoreObserver(subject, str), m_window(window)
    {
        m_font.loadFromFile("./res/font/font.ttf");
        m_text.setFont(m_font);
        m_text.setString(str + "0000000");
        m_text.setColor(sf::Color::White);
        m_text.scale(0.7, 0.7);

        auto trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(m_pos);
        m_text.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    /**
     * Draws the score to the screen.
     */
    void ScoreObserver::draw() const
    {
        m_window->draw(m_text);
    }

    /**
     * Updates the text to draw to the screen.
     */
    void ScoreObserver::updateDrawable()
    {
        auto countDigit = [](int num) -> int{
            int count = 0;
            while(num != 0){
                num/=10;
                count++;
            }
            return count;
        };
        int digitNum = countDigit(m_score);
        std::string str;
        while(digitNum < 7){
            str += '0';
            digitNum++;
        }
        str += std::to_string(m_score);
        m_text.setString(m_string + str);
    }

} // namespace RoadFighterSFML

