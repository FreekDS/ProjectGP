#include <Game.h>
#include <EntityFactory.h>
#include <Player.h>
#include <World.h>
#include <GLL/Transformation.h>
#include <Observer.h>
#include <GLL/Clock.h>

namespace RoadFighterSFML {

    /**
     * Constructor for Game.
     * The constructor initializes the SFML Window including creation of Icon.
     * The @see Transformation Singleton class is updated with the screen sizes.
     * @param title Title of the window which is "Road Fighter" by default.
     * @param fullscreen Enable or disable fullscreen, by default this is true.
     * @param debug Enable or disable debug information, by default this is false.
     */
    Game::Game(const string& title, bool fullscreen, bool debug) : m_debug(debug)
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
    }

    /**
     * Runs the game
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

        RoadFighter::Clock clock;
        double gameTick = 1.0 / 120.0;

        while (m_window->isOpen()) {
            if (clock.getTimeAsSeconds()>=gameTick) {
                clock.reset();
                // Handle events
                handleSFMLEvents();
                // Update the world
                m_world->update();

            }
                // Clear the window
                m_window->clear(sf::Color::Black);
                // Draw to window
                m_world->draw();
                // Display the window
                m_window->display();

        }
    }

    /**
     * Handles the Events of SFML.
     * Closes window when pressed on close button.
     * Allows alt + tab (gained focus and lost focus).
     * Allows escape to close game using escape.
     */
    void Game::handleSFMLEvents() const
    {
        sf::Event event{};
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
                break;
            default:
                break;
            }
    }
}