#include <Game.h>
#include <Player.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    Game::Game(const string& title, bool fullscreen)
    {
        // Initialize the window
        sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
        if (fullscreen)
            m_window = make_shared<sf::RenderWindow>(videoMode, title,
                    sf::Style::None);
        else
            m_window = make_shared<sf::RenderWindow>(videoMode, title,
                    sf::Style::Default);
        sf::Image icon;
        icon.loadFromFile("./res/sprites/ui/icon.png");
        m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        // Initialize the Transformation class with the window size
        auto trans = RoadFighter::Transformation::getInstance();
        trans->setScreenSize(m_window->getSize().x, m_window->getSize().y);
    }

    void Game::runGame()
    {
        // create a player for testing purpose
        Player player("player_car.png", m_window);

        while (m_window->isOpen()) {
            // Handle events
            handleSFMLEvents();

            // Clear the window
            sf::Color color(110, 208, 226);
            m_window->clear(color);

            // Draw to window
            // todo
            player.draw();

            // Display the window
            m_window->display();
        }
    }

    /**
     * Handles the Events of SFML
     * Closes window when pressed on close button
     * Allows alt + tab (gained focus and lost focus)
     * Allows escape to close game using escape
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