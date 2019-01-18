#ifndef ROADFIGHTER_SCOREBOARD_H
#define ROADFIGHTER_SCOREBOARD_H

#include <iostream>
#include <array>

namespace RoadFighter {

    struct ScoreEntry{
        std::string name;
        std::string score;
    };

    class Scoreboard {
    protected:
        std::array<ScoreEntry, 5> m_scoreBoard;
        std::string m_score_file;
        bool m_askInput;
        unsigned int m_currentScore;
        int m_currentPos;
        bool m_scoreSet;
    public:
        explicit Scoreboard(const std::string& score_file = "score.ini");

        virtual void update();

        virtual void draw() const;

        static void resetScores(const std::string& score_file = "score.ini");

        int checkScore(unsigned int score);

        void updateScoreboard(std::string& name);

        virtual ~Scoreboard();

        virtual void updateDrawable(unsigned int pos){};

        bool needsInput() const;

        virtual void addInput(const std::string& input){}

        virtual void confirmInput() = 0;

        virtual void removeCharOfInput(){}

        void setPlayerScore(unsigned int score, unsigned int finish_pos);

        virtual void setDrawableText(unsigned int score, unsigned int finish_pos) = 0;

        bool scoreIsSet() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_SCOREBOARD_H
