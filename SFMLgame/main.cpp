#include <iostream>
#include <memory>
#include <Player.h>
#include <GLL/Transformation.h>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace RoadFighter;

int main(int argc, char* argv[])
{
    sf::VideoMode fullscreen = sf::VideoMode::getDesktopMode();
    string title = "Road Fighter";
    shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(fullscreen, title,
            sf::Style::None);
    cout << "Screen size: " << window->getSize().x << "x" << window->getSize().y << endl;
    sf::Image icon;
    icon.loadFromFile("./res/sprites/entity/player_car.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
            case sf::Event::LostFocus:
                window->setActive(false);
            case sf::Event::GainedFocus:
                window->setActive(true);
            default:
                break;
            }
        }
        sf::Color col(110,208,226);
        window->clear(col);
        p.draw();
        window->display();
    }
    return EXIT_SUCCESS;
}

