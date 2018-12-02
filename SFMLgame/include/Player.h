#ifndef ROADFIGHTER_SFML_PLAYER_H
#define ROADFIGHTER_SFML_PLAYER_H

#include <memory>
#include "GLL/Player.h"
#include "SFML/Graphics.hpp"

using namespace std;

namespace RoadFighterSFML {

    class Player : public RoadFighter::Player {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        shared_ptr<sf::RenderWindow> m_window;
    public:
        Player(const sf::Sprite& sprite, shared_ptr<sf::RenderWindow>& window);
        Player(const std::string& file_name, shared_ptr<sf::RenderWindow>& window);
        ~Player() override;
        void updateSpriteLocation();

        void update() override;

        bool canBeDestroyed() override;

        void draw() const override;
    };

}

#endif //ROADFIGHTER_SFML_PLAYER_H
