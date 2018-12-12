#ifndef ROADFIGHTER_SFML_GAME_H
#define ROADFIGHTER_SFML_GAME_H

#include <GLL/Game.h>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

    class Game : public RoadFighter::Game {
    private:
        shared_ptr<sf::RenderWindow> m_window;
        bool m_debug;
    public:
        /**
         * Constructor for Game
         * The constructor initializes the SFML Window including creation of Icon
         * The @see Transformation Singleton class is updated with the screen sizes
         * @param title Title of the window which is "Road Fighter" by default
         * @param fullscreen Enable or disable fullscreen, by default this is true
         * @param debug Enable or disable debug information, by default this is false
         */
        explicit Game(const string& title = "Road Fighter", bool fullscreen = true, bool debug = false);

        /**
         * Runs the game
         *
         * 1. Handle events using @see handleSFMLEvents()
         * 2. Clears the window
         * 3. Draws to the window
         * 4. displays the window
         *
         * This function has the Game Loop which runs until the window is closed
         */
        void runGame() override;

        /**
         * Handles the Events of SFML
         * Closes window when pressed on close button
         * Allows alt + tab (gained focus and lost focus)
         */
        void handleSFMLEvents() const;
    };

}

#endif //ROADFIGHTER_SFML_GAME_H
