#ifndef ROADFIGHTER_SFML_SCOREBOARD_H
#define ROADFIGHTER_SFML_SCOREBOARD_H

#include <GLL/Scoreboard.h>
#include <memory>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

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

    class Scoreboard : public RoadFighter::Scoreboard {
    private:
        std::array<ScoreEntry, 5> m_sfmlScores;
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Text m_askName;
        sf::Text m_name;
        sf::Text m_score;
        sf::Font m_font;
    public:
        void draw() const override;

        Scoreboard(const std::string& score_file = "score.ini");

        Scoreboard(std::shared_ptr<sf::RenderWindow>& window, const std::string& score_file = "score.ini");

        void updateDrawable(unsigned int pos) override;

        void confirmInput() override;

        void setWindow(const std::shared_ptr<sf::RenderWindow>& window);

        void addInput(const std::string& input) override;

        void removeCharOfInput() override;

        void init();

        void setDrawableText(unsigned int score, unsigned int finish_pos) override;
    };

} // namespace RoadFighterSFML

#endif //ROADFIGHTER_SFML_SCOREBOARD_H
