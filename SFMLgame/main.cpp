#include <iostream>
#include <memory>
#include <Player.h>
#include "SFML/Graphics.hpp"
#include "GLL/Transformation.h"

using namespace std;
using namespace RoadFighter;

int main(int argc, char* argv[])
{
    shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Road Fighter",
            sf::Style::None);
    shared_ptr<Transformation> trans = Transformation::getInstance();
    trans->setScreenSize(window->getSize().x, window->getSize().y);
    RoadFighterSFML::Player p("player_car.png", window);

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::Escape)
                    window->close();
            default:
                break;
            }
        }
        window->clear(sf::Color::Blue);
        p.draw();
        window->display();
    }
    return EXIT_SUCCESS;
}

