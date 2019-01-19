#include <Scoreboard.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

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

    /**
     * Updates the drawable of the scoreboard.
     * All scores are shifted to the correct position. The last score will be erased.
     * @param pos Position of the updated element.
     */
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

    /**
     * Sets the SFML window
     * @param window Shared pointer to the window
     */
    void Scoreboard::setWindow(const std::shared_ptr<sf::RenderWindow>& window)
    {
        m_window = window;
        init();
    }

    /**
     * Adds input received from the keyboard to the name.
     * @param input Input received from the keyboard.
     */
    void Scoreboard::addInput(const std::string& input)
    {
        auto trans = RoadFighter::Transformation::getInstance();
        std::string name = m_name.getString();
        name += input;
        m_name.setString(name);
        float xpos = trans->getWindowWidth()/2.0f-m_name.getGlobalBounds().width/2;
        m_name.setPosition(xpos, m_name.getPosition().y);
    }

    /**
     * Initializes the texts of the scoreboard.
     * Things like position, scale, font and color will be initialized for all texts.
     */
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

    /**
     * This function removes a character of the input when backspace is pressed.
     */
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

    /**
     * This function confirms the input given by the keyboard only if enter is pressed.
     * If enter is pressed, the scoreboard will stop asking for keyboard input. @see needsInput()
     */
    void Scoreboard::confirmInput()
    {
        if(!m_acceptDelay.timerFinished())
            return;
        if(m_name.getString().toAnsiString().empty())
            return;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
            std::string name = m_name.getString().toAnsiString();
            updateScoreboard(name);
            m_askInput = false;
        }
    }

    /**
     * This function will update the drawable text with the score and finish position of the player.
     * @param score Score to set.
     * @param finish_pos Finish position of the player.
     */
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


} // namespace RoadFighterSFML