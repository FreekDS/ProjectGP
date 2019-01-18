#include <Scoreboard.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    Scoreboard::Scoreboard(std::shared_ptr<sf::RenderWindow>& window, const std::string& score_file)
            :RoadFighter::Scoreboard(score_file), m_window(window)
    {
        init();
    }

    void Scoreboard::draw() const
    {
        if (m_askInput) {
            m_window->draw(m_askName);
            m_window->draw(m_name);
        }
        for (auto& entry : m_sfmlScores) {
            m_window->draw(entry.name);
            m_window->draw(entry.score);
        }
        m_window->draw(m_score);
    }

    void Scoreboard::updateDrawable(unsigned int pos)
    {
        m_sfmlScores[pos].score.scale(1.1, 1.1);
        m_sfmlScores[pos].name.scale(1.1, 1.1);
        m_sfmlScores[pos].name.setColor(sf::Color::Red);
        m_sfmlScores[pos].score.setColor(sf::Color::Red);
        for(unsigned int i = 0; i<m_scoreBoard.size(); i++)
        {
            m_sfmlScores[i].name.setString("\t"+std::to_string(i+1)+".\t"+m_scoreBoard[i].name);
            m_sfmlScores[i].score.setString("\t\t\t"+m_scoreBoard[i].score);
        }
    }

    Scoreboard::Scoreboard(const string& score_file)
            :RoadFighter::Scoreboard(score_file)
    {
        init();
    }

    void Scoreboard::setWindow(const std::shared_ptr<sf::RenderWindow>& window)
    {
        m_window = window;
        init();
    }

    void Scoreboard::addInput(const std::string& input)
    {
        auto trans = RoadFighter::Transformation::getInstance();
        m_name.setString(m_name.getString()+input);
        float xpos = trans->getWindowWidth()/2.0f-m_name.getGlobalBounds().width/2;
        m_name.setPosition(xpos, m_name.getPosition().y);
    }

    void Scoreboard::init()
    {
        auto trans = RoadFighter::Transformation::getInstance();
        float xpos = 0;
        auto ypos = static_cast<float>(trans->getWindowHeight()/4.0);
        for (unsigned int i = 0; i<m_sfmlScores.size(); i++) {
            m_sfmlScores[i].name.setString("\t"+std::to_string(i+1)+".\t"+m_scoreBoard[i].name);
            m_sfmlScores[i].score.setString("\t\t\t"+m_scoreBoard[i].score);
            m_sfmlScores[i].name.setPosition(xpos, ypos);
            ypos += m_sfmlScores[i].name.getGlobalBounds().height*1.5f;
            m_sfmlScores[i].score.setPosition(xpos, ypos);
            ypos += m_sfmlScores[i].score.getGlobalBounds().height*2.0f;

        }
        m_font.loadFromFile("./res/font/font.ttf");

        m_score.setFont(m_font);
        m_score.setColor(sf::Color::White);
        m_score.setString("You finished 0th! Your score: 0000000");
        m_score.setPosition(trans->getWindowWidth()/2.0f-m_score.getGlobalBounds().width/2,
                m_score.getGlobalBounds().height);

        m_askName.setColor(sf::Color::Blue);
        m_askName.setFont(m_font);
        m_askName.setString("New Highscore! Enter name and press enter...");
        m_askName.setPosition(trans->getWindowWidth()/2.0f-m_askName.getGlobalBounds().width/2,
                m_score.getGlobalBounds().height+m_score.getGlobalBounds().height*1.5f);

        m_name.setFont(m_font);
        m_name.setColor(sf::Color::White);
        m_name.setPosition(0, m_askName.getPosition().y+m_askName.getGlobalBounds().height*1.5f);


    }

    void Scoreboard::removeCharOfInput()
    {
        auto trans = RoadFighter::Transformation::getInstance();
        std::string name = m_name.getString();
        if (!name.empty()) {
            m_name.setString(name.substr(0, name.size()-1));
            float xpos = trans->getWindowWidth()/2.0f-m_name.getGlobalBounds().width/2;
            m_name.setPosition(xpos, m_name.getPosition().y);
        }
    }

    void Scoreboard::confirmInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            std::string name = m_name.getString().toAnsiString();
            updateScoreboard(name);
            m_askInput = false;
        }
    }

    void Scoreboard::setDrawableText(unsigned int score, unsigned int finish_pos)
    {
        auto countDigit = [](int num) -> int {
            int count = 0;
            while (num!=0) {
                num /= 10;
                count++;
            }
            return count;
        };
        int digitNum = countDigit(score);
        std::string str;
        while (digitNum<7) {
            str += '0';
            digitNum++;
        }
        str += std::to_string(score);
        std::string racePos;
        if(finish_pos == 1){
            racePos = "1st";
        }
        else if(finish_pos == 2){
            racePos = "2nd";
        }
        else{
            racePos = std::to_string(finish_pos) + "th";
        }
        m_score.setString("You finished " + racePos + "! Your score: " + str);
    }


}