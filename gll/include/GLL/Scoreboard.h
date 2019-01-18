#ifndef ROADFIGHTER_SCOREBOARD_H
#define ROADFIGHTER_SCOREBOARD_H

#include <iostream>
#include <array>
#include "Clock.h"

namespace RoadFighter {

    /**
     * This structure represents an entity of the scoreboard.
     * A scoreboard entry has a name and a score.
     */
    struct ScoreEntry {
        std::string name;
        std::string score;
    };

    /**
     * This class represents the basics of a scoreboard.
     * A scoreboard has:
     * - An array to hold the scoreboard entries
     * - A string which contains the filename of the score information
     * - A bool to check whether there is asked for input
     * - An unsigned integer to hold the current score
     * - An integer which determines the current position in the scoreboard (-1 if it is not on the board)
     * - A bool to check if setScore function is called or not
     * - An accept delay clock to prevent from instantly confirming your high score
     */
    class Scoreboard {
    protected:
        std::array<ScoreEntry, 5> m_scoreBoard;
        std::string m_score_file;
        bool m_askInput;
        unsigned int m_currentScore;
        int m_currentPos;
        bool m_scoreSet;
        Clock m_acceptDelay;
    public:

        /**
         * Explicit constructor which constructs a basic scoreboard.
         * This constructor reads the ini file containing the scores and parses it to
         * its data structure.
         * The constructor will look in the folder ./res/scores/ for the score file.
         * @param score_file File name of the scores file, default "score.ini".
         */
        explicit Scoreboard(const std::string& score_file = "score.ini");

        /**
         * Updates the scoreboard.
         * If input is asked, it checks if the input needs to be confirmed.
         */
        void update();

        /**
         * Virtual draw function.
         * If the function is called from this Base class, it will print the scores
         * the the std::cout stream.
         */
        virtual void draw() const;

        /**
         * Resets the score file to some base values.
         * This function will write the score file in the folder ./res/scores/
         * @param score_file File name of the scores, default "score.ini".
         */
        static void resetScores(const std::string& score_file = "score.ini");

        /**
         * Checks the score and determine the position in the scoreboard.
         * @param score Score to check.
         * @return Position in the scoreboard, -1 if the score is not eligible on the scoreboard.
         */
        int checkScore(unsigned int score);

        /**
         * Updates the scoreboard and adds a name to the scoreboard entry.
         * @param name Name to add to the scoreboard entry.
         */
        void updateScoreboard(std::string& name);

        /**
         * Destructor of the scoreboard.
         * When the scoreboard is destructed, the scores are written back to the .ini file.
         * The name of this file is stored as member of the scoreboard.
         */
        virtual ~Scoreboard();

        /**
         * Updates the drawable of the scoreboard.
         * All scores are shifted to the correct position. The last score will be erased.
         * @param pos Position of the updated element.
         */
        virtual void updateDrawable(unsigned int pos) = 0;

        /**
         * This function checks if keyboard input is asked by the scoreboard.
         * The value returned by this function is stored as member of the scoreboard.
         * @return True if keyboard input is asked by the scoreboard.
         */
        bool needsInput() const;

        /**
         * Adds input received from the keyboard to the name.
         * @param input Input received from the keyboard.
         */
        virtual void addInput(const std::string& input) = 0;

        /**
         * This function confirms the input given by the keyboard only if enter is pressed.
         * If enter is pressed, the scoreboard will stop asking for keyboard input. @see needsInput()
         */
        virtual void confirmInput() = 0;

        /**
         * This function removes a character of the input when backspace is pressed.
         */
        virtual void removeCharOfInput() = 0;

        /**
         * Sets the score and finish position of the player.
         * If this function is called @see scoreIsSet() will return true, else it will return false.
         * @param score Score of the player
         * @param finish_pos Finish position of the player
         */
        void setPlayerScore(unsigned int score, unsigned int finish_pos);

        /**
         * This function will update the drawable text with the score and finish position of the player.
         * @param score Score to set.
         * @param finish_pos Finish position of the player.
         */
        virtual void setDrawableText(unsigned int score, unsigned int finish_pos) = 0;

        /**
         * This function will return true if the scores of the player are set.
         * @return True if the scores of the player are set.
         */
        bool scoreIsSet() const;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_SCOREBOARD_H
