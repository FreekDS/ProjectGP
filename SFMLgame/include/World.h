#ifndef ROADFIGHTER_SFML_WORLD_H
#define ROADFIGHTER_SFML_WORLD_H

#include <GLL/World.h>
#include <SFML/Graphics.hpp>
#include "Player.h"

using keymap = map<string, sf::Keyboard::Key>;

namespace RoadFighterSFML {

    class World : public RoadFighter::World {
    private:
        sf::Sprite m_sprite;
        sf::Sprite m_sprite2;
        sf::Texture m_texture;
        window_ptr m_window;
        keymap m_keymap;
    public:

        World(const string& file_name, window_ptr& window);

        void draw() const override;

        void update() override;

        void readInput();

        void initializeKeymap();

        void backgroundLoopUpdate(sf::Sprite& toMove, sf::Sprite& other);
    };

}

#endif //ROADFIGHTER_SFML_WORLD_H
