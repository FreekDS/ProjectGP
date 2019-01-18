#ifndef ROADFIGHTER_SFML_SCOREBOARD_H
#define ROADFIGHTER_SFML_SCOREBOARD_H

#include <GLL/Scoreboard.h>
#include <memory>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

    /**
     * This is the SFML variant of the GLL ScoreEntry.
     * An entry has a font, a name and a score.
     */
    struct ScoreEntry {
        ScoreEntry(){
            font.loadFromFile("./res/font/font.ttf");
            name.setColor(sf::Color::White);
            name.setFont(font);
            score.setColor(sf::Color::White);
            score.setFont(font);
            name.scale(0.7, 0.7);
            score.scale(0.7, 0.7);
        }
        sf::Text name;
        sf::Text score;
        sf::Font font;
    };

    /**
     * This class is derived from RoadFighter::Scoreboard
     * The SFML Scoreboard has:
     * - an array containing the SFML version of the scores
     * - a shared pointer to the SFML window
     * - a text to ask the player to enter his name
     * - a text to store the player's input as he is typing
     * - a text to hold the score of the player
     * - a font used for the previous text elements
     */
    class Scoreboard : public RoadFighter::Scoreboard {
    private:
        std::array<ScoreEntry, 5> m_sfmlScores;
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Text m_askName;
        sf::Text m_name;
        sf::Text m_score;
        sf::Font m_font;
    public:

        /**
         * This function draws the scoreboard and all its elements to the SFML window.
         * Things that will be drawn at all times:
         * - score of the player
         * - the scoreboard
         * Things that will be draw if the player reached a high score:
         * - the query for a name
         * - the name the user is typing
         * - the new high score will be drawn in red after the player confirmed his name
         */
        void draw() const override;

        /**
         * Constructor for the scoreboard.
         * This constructor calls the constructor of its base class.
         * @see init() is called to initialize the texts.
         * @param score_file File which contains the scores.
         */
        explicit Scoreboard(const std::string& score_file = "score.ini");

        /**
         * Updates the drawable of the scoreboard.
         * All scores are shifted to the correct position. The last score will be erased.
         * @param pos Position of the updated element.
         */
        void updateDrawable(unsigned int pos) override;

        /**
         * This function confirms the input given by the keyboard only if enter is pressed.
         * If enter is pressed, the scoreboard will stop asking for keyboard input. @see needsInput()
         */
        void confirmInput() override;

        /**
         * Sets the SFML window
         * @param window Shared pointer to the window
         */
        void setWindow(const std::shared_ptr<sf::RenderWindow>& window);

        /**
         * Adds input received from the keyboard to the name.
         * @param input Input received from the keyboard.
         */
        void addInput(const std::string& input) override;

        /**
         * This function removes a character of the input when backspace is pressed.
         */
        void removeCharOfInput() override;

        /**
         * Initializes the texts of the scoreboard.
         * Things like position, scale, font and color will be initialized for all texts.
         */
        void init();

        /**
         * This function will update the drawable text with the score and finish position of the player.
         * @param score Score to set.
         * @param finish_pos Finish position of the player.
         */
        void setDrawableText(unsigned int score, unsigned int finish_pos) override;
    };

} // namespace RoadFighterSFML

#endif //ROADFIGHTER_SFML_SCOREBOARD_H
