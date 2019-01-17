#ifndef ROADFIGHTER_SFML_OBSERVER_H
#define ROADFIGHTER_SFML_OBSERVER_H

#include <GLL/Observer.h>
#include <GLL/Player.h>
#include <SFML/Graphics.hpp>

using window_ptr = shared_ptr<sf::RenderWindow>;

namespace RoadFighterSFML {

    /**
     * This class is the SFML implementation of the SpeedObserver.
     * A SFML SpeedObserver has:
     * - A pointer to the window.
     * - A font.
     * - Two texts: one with information, one with a speed value.
     */
    class SpeedObserver : public RoadFighter::SpeedObserver {
    private:
        window_ptr m_window;
        sf::Font m_font;
        sf::Text m_text;
        sf::Text m_value;
    public:
        /**
         * Constructor for SpeedObserver.
         * This constructor initializes the font with the font "./res/font/font.ttf".
         * The SFML text is initialized with the string of the base class + 0.
         * The position of the text is determined by converting m_pos to screen coordinates..
         * @param subject Subject to observe (Player).
         * @param str String with additional information ex. 'Speed: '.
         * @param window Window to draw results to.
         */
        SpeedObserver(const shared_ptr<RoadFighter::Player>& subject, const string& str, const window_ptr& window);

        /**
         * Updates the SpeedObserver.
         * - Changes SFML text to string of base class + speed of subject.
         * - Draws the text to the screen.
         */
        void update() override;

        /**
         * Draws the observer to the window.
         */
        void draw() const override;

        /**
         * Updates the text color based on the speed of the player.
         */
        void updateTextColor();
    };

    class ScoreObserver : public RoadFighter::ScoreObserver{
    private:
        window_ptr m_window;
        sf::Font m_font;
        sf::Text m_text;
    public:
        void draw() const override;

        void updateDrawable() override;

        ScoreObserver(const shared_ptr<RoadFighter::Player>& subject, const string& str, const window_ptr& window);
    };

} // namespace RoadFighterSFML

#endif //ROADFIGHTER_SFML_OBSERVER_H
