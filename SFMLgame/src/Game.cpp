#include <Game.h>
#include <EntityFactory.h>
#include <World.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    /**
     * Constructor for Game.
     * The constructor initializes the SFML Window including creation of Icon.
     * The @see Transformation Singleton class is updated with the screen sizes.
     * @param title Title of the window which is "Road Fighter" by default.
     * @param fullscreen Enable or disable fullscreen, by default this is true.
     * @param debug Enable or disable debug information, by default this is false.
     */
    Game::Game(const string& title, bool fullscreen, bool debug)
            :m_debug(debug), m_state(GameState::NONE), m_scoreboard()
    {
        // Initialize the window
        sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
        if (fullscreen)
            m_window = make_shared<sf::RenderWindow>(videoMode, title,
                    sf::Style::None);
        else
            m_window = make_shared<sf::RenderWindow>(sf::VideoMode(900, 600), title,
                    sf::Style::Titlebar | sf::Style::Close);
        sf::Image icon;
        icon.loadFromFile("./res/sprites/ui/icon.png");
        m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        // Initialize the Transformation class with the window size
        auto trans = RoadFighter::Transformation::getInstance();
        trans->setScreenSize(m_window->getSize().x, m_window->getSize().y);

        // Initialize the world of the Game
        m_world = make_shared<World>("background.png", m_window, m_debug);

        m_scoreboard.setWindow(m_window);
    }

    /**
     * Runs the game.
     * Changes the game state if needed
     *
     * 1. Handle events using @see handleSFMLEvents().
     * 2. Clears the window.
     * 3. Draws to the window.
     * 4. displays the window.
     *
     * This function has the Game Loop which runs until the window is closed.
     */
    void Game::runGame()
    {
        // create a player for testing purpose
        auto entityFac = make_shared<EntityFactory>(m_window);
        m_world->add(entityFac->createPlayer());
        m_world->setFactory(entityFac);
        m_world->setupRaceCars();

        m_state = GameState::PLAYING;

        RoadFighter::Clock clock;
        double gameTick = 1.0/120.0;

        while (m_window->isOpen()) {
            // handle events
            handleSFMLEvents();

            if (m_state==GameState::PLAYING) {
                if (clock.getTimeAsSeconds()>=gameTick) {
                    clock.reset();

                    // Update the world
                    m_world->update();

                    // check if the game has finished and change game state if so
                    if (m_world->gameFinished()){
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                            m_state = GameState::SCOREBOARD;
                    }

                }
            }
            else if (m_state==GameState::SCOREBOARD) {
                if (!m_scoreboard.scoreIsSet()) {
                    m_scoreboard.setPlayerScore(m_world->getScore(), 6 - m_world->getRaceCarsBehindPlayer());
                }
                m_scoreboard.update();
            }

            // Always clear the window
            m_window->clear(sf::Color::Black);

            // Draw to window according to the game state
            if (m_state==GameState::PLAYING)
                m_world->draw();
            else if (m_state==GameState::SCOREBOARD)
                m_scoreboard.draw();

            // Always display the window
            m_window->display();

        }


    }

    /**
     * Handles the Events of SFML.
     * Closes window when pressed on close button.
     * Allows alt + tab (gained focus and lost focus).
     * Allows escape to close game using escape.
     */
    void Game::handleSFMLEvents()
    {
        sf::Event event{};
        string input;
        while (m_window->pollEvent(event))
            switch (event.type) {
                // Close window with close button
            case sf::Event::Closed:
                m_window->close();
                break;
                // Allows losing focus of window by setting the window to inactive
            case sf::Event::LostFocus:
                m_window->setActive(false);
                break;
                // Allows gaining focus of window by setting the window to active
            case sf::Event::GainedFocus:
                m_window->setActive(true);
                break;
                // Allows the window to close with Escape
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::Escape)
                    m_window->close();
                if (m_state==GameState::SCOREBOARD)
                    if (event.key.code==sf::Keyboard::BackSpace)
                        if (m_scoreboard.needsInput())
                            m_scoreboard.removeCharOfInput();
                break;
            case sf::Event::TextEntered:
                if (m_state==GameState::SCOREBOARD) {
                    if (m_scoreboard.needsInput()) {
                        if (event.text.unicode<0x80 && event.text.unicode>0x30)
                            input += static_cast<char>(event.text.unicode);
                        if (event.text.unicode==0x20)
                            input += ' ';
                        m_scoreboard.addInput(input);
                    }
                }

            default:
                break;
            }
    }
}