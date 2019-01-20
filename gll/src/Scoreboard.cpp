#include <GLL/Scoreboard.h>
#include <lib/ini.h>

namespace RoadFighter {

    /**
     * Explicit constructor which constructs a basic scoreboard.
     * This constructor reads the ini file containing the scores and parses it to
     * its data structure.
     * The constructor will look in the folder ./res/scores/ for the score file.
     * @param score_file File name of the scores file.
     */
    Scoreboard::Scoreboard(const std::string& score_file)
            :m_score_file(score_file), m_askInput(false), m_scoreSet(false), m_acceptDelay(500)
    {
        std::string path = "./res/score/";
        mINI::INIFile file(path+score_file);
        mINI::INIStructure ini;
        file.read(ini);
        for (unsigned int i = 0; i<m_scoreBoard.size(); i++) {
            std::string head = "Score"+std::to_string(i);
            std::string name = ini.get(head).get("name");
            std::string score = ini.get(head).get("score");
            m_scoreBoard[i].name = name;
            m_scoreBoard[i].score = score;
        }
    }

    /**
     * Virtual draw function.
     * If the function is called from this Base class, it will print the scores
     * the the std::cout stream.
     */
    void Scoreboard::draw() const
    {
        for (unsigned int i = 1; i<=m_scoreBoard.size(); i++) {
            std::cout << i << ".\tname: " << m_scoreBoard[i-1].name << std::endl;
            std::cout << "\tscore: " << m_scoreBoard[i-1].score << std::endl << std::endl;
        }
    }

    /**
     * Resets the score file to some base values.
     * This function will write the score file in the folder ./res/scores/
     * @param score_file File name of the scores, default "score.ini".
     */
    void Scoreboard::resetScores(const std::string& score_file)
    {
        std::string path = "./res/score/";
        mINI::INIFile file(path+score_file);
        mINI::INIStructure ini;
        file.read(ini);
        ini["Score0"]["name"] = "donald trump";
        ini["Score0"]["score"] = "0010000";
        ini["Score1"]["name"] = "elon musk";
        ini["Score1"]["score"] = "0009000";
        ini["Score2"]["name"] = "bernard theofiel waterslaeghers";
        ini["Score2"]["score"] = "0008888";
        ini["Score3"]["name"] = "de kotmadam";
        ini["Score3"]["score"] = "0008500";
        ini["Score4"]["name"] = "jacques vermeire";
        ini["Score4"]["score"] = "0001000";
        file.write(ini);
    }

    /**
     * Checks the score and determine the position in the scoreboard.
     * @param score Score to check.
     * @return Position in the scoreboard, -1 if the score is not eligible on the scoreboard.
     */
    int Scoreboard::checkScore(const unsigned int score)
    {
        for (unsigned int i = 0; i<m_scoreBoard.size(); i++) {
            auto scoreBoardScore = static_cast<unsigned int>(std::stoi(m_scoreBoard[i].score));
            if (score>=scoreBoardScore)
                return i;
        }
        return -1;
    }

    /**
     * Updates the scoreboard and adds a name to the scoreboard entry.
     * @param name Name to add to the scoreboard entry.
     */
    void Scoreboard::updateScoreboard(std::string& name)
    {
        if(m_currentPos<0)
            return;
        auto countDigit = [](int num) -> int {
            int count = 0;
            while (num!=0) {
                num /= 10;
                count++;
            }
            return count;
        };
        int digitNum = countDigit(m_currentScore);
        std::string score;
        while (digitNum<7) {
            score += '0';
            digitNum++;
        }
        score += std::to_string(m_currentScore);
        auto pos = static_cast<unsigned int>(m_currentPos);
        std::string oldName;
        std::string oldScore;
        while(pos < m_scoreBoard.size()){
            // store old variables
            oldName = m_scoreBoard[pos].name;
            oldScore = m_scoreBoard[pos].score;
            // update
            m_scoreBoard[pos].name = name;
            m_scoreBoard[pos].score = score;
            pos++;
            name = oldName;
            score = oldScore;
        }
        updateDrawable(static_cast<unsigned int>(m_currentPos));
    }

    /**
     * Destructor of the scoreboard.
     * When the scoreboard is destructed, the scores are written back to the .ini file.
     * The name of this file is stored as member of the scoreboard.
     */
    Scoreboard::~Scoreboard()
    {
        // write back the possible changed results
        std::string path = "./res/score/";
        mINI::INIFile file(path+m_score_file);
        mINI::INIStructure ini;
        file.read(ini);
        for (unsigned int i = 0; i<m_scoreBoard.size(); i++) {
            std::string head = "Score" + std::to_string(i);
            ini[head]["name"] = m_scoreBoard[i].name;
            ini[head]["score"] = m_scoreBoard[i].score;
        }
        file.write(ini);
    }

    /**
     * Updates the scoreboard.
     * If input is asked, it checks if the input needs to be confirmed.
     */
    void Scoreboard::update()
    {
        if(m_askInput){
            confirmInput();
        }
    }

    /**
     * This function checks if keyboard input is asked by the scoreboard.
     * The value returned by this function is stored as member of the scoreboard.
     * @return True if keyboard input is asked by the scoreboard.
     */
    bool Scoreboard::needsInput() const
    {
        return m_askInput;
    }

    /**
     * Sets the score and finish position of the player.
     * If this function is called @see scoreIsSet() will return true, else it will return false.
     * @param score Score of the player
     * @param finish_pos Finish position of the player
     */
    void Scoreboard::setPlayerScore(unsigned int score, unsigned int finish_pos)
    {
        score += (6-finish_pos) * 1000;
        m_currentScore = score;
        m_currentPos = checkScore(score);
        m_askInput = m_currentPos>=0;
        setDrawableText(score, finish_pos);
        m_scoreSet = true;
        m_acceptDelay.setTimer(100);
        m_acceptDelay.startTimer();
    }

    /**
     * This function will return true if the scores of the player are set.
     * @return True if the scores of the player are set.
     */
    bool Scoreboard::scoreIsSet() const
    {
        return m_scoreSet;
    }


} // namespace RoadFighter
