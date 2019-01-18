#include <GLL/Scoreboard.h>
#include <lib/ini.h>

namespace RoadFighter {

    Scoreboard::Scoreboard(const std::string& score_file)
            :m_score_file(score_file), m_askInput(false), m_scoreSet(false)
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

    void Scoreboard::draw() const
    {
        for (unsigned int i = 1; i<=m_scoreBoard.size(); i++) {
            std::cout << i << ".\tname: " << m_scoreBoard[i-1].name << std::endl;
            std::cout << "\tscore: " << m_scoreBoard[i-1].score << std::endl << std::endl;
        }
    }

    void Scoreboard::resetScores(const std::string& score_file)
    {
        std::cerr << "reset" << std::endl;
        std::string path = "./res/score/";
        mINI::INIFile file(path+score_file);
        mINI::INIStructure ini;
        file.read(ini);
        ini["Score0"]["name"] = "Donald Trump";
        ini["Score0"]["score"] = "0010000";
        ini["Score1"]["name"] = "Mickey Mouse";
        ini["Score1"]["score"] = "0009000";
        ini["Score2"]["name"] = "Alan Walker";
        ini["Score2"]["score"] = "0008888";
        ini["Score3"]["name"] = "De Kotmadam";
        ini["Score3"]["score"] = "0008500";
        ini["Score4"]["name"] = "Jacques Vermeire";
        ini["Score4"]["score"] = "0001000";
        file.write(ini);
    }

    int Scoreboard::checkScore(const unsigned int score)
    {
        for (unsigned int i = 0; i<m_scoreBoard.size(); i++) {
            auto scoreBoardScore = static_cast<unsigned int>(std::stoi(m_scoreBoard[i].score));
            if (score>=scoreBoardScore)
                return i;
        }
        return -1;
    }

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

    void Scoreboard::update()
    {
        if(m_askInput){
            confirmInput();
        }
    }

    bool Scoreboard::needsInput() const
    {
        return m_askInput;
    }

    void Scoreboard::setPlayerScore(unsigned int score, unsigned int finish_pos)
    {
        score += (6-finish_pos) * 1000;
        m_currentScore = score;
        m_currentPos = checkScore(score);
        m_askInput = m_currentPos>=0;
        setDrawableText(score, finish_pos);
        m_scoreSet = true;
    }

    bool Scoreboard::scoreIsSet() const
    {
        return m_scoreSet;
    }


} // namespace RoadFighter
