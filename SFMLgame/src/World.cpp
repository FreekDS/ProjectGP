#include <World.h>
#include <iostream>

namespace RoadFighterSFML{

    void World::draw() const
    {
        m_window->draw(m_sprite);
        for(const auto& entity : m_childEntities){
            entity->draw();
        }
    }

    void World::update()
    {
        readInput();
    }

    World::World(const string& file_name, window_ptr& window) : m_window(window)
    {
        string path = "./res/sprites/ui/";
        m_texture.loadFromFile(path + file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);
        initializeKeymap();
    }

    void World::readInput()
    {
        if(sf::Keyboard::isKeyPressed(m_keymap["up"])){
            // move player up
        }
        if(sf::Keyboard::isKeyPressed(m_keymap["down"])){
            // move player down
        }
        if(sf::Keyboard::isKeyPressed(m_keymap["left"])){
            // move player left
        }
        if(sf::Keyboard::isKeyPressed(m_keymap["right"])){
            // move player right
        }
        if(sf::Keyboard::isKeyPressed(m_keymap["shoot"])){
            // let player shoot a bullet
        }
        if(sf::Keyboard::isKeyPressed(m_keymap["speedup"])){
            // player accelerates
        }

    }

    void World::initializeKeymap()
    {
        m_keymap["up"] = sf::Keyboard::Up;
        m_keymap["down"] = sf::Keyboard::Down;
        m_keymap["left"] = sf::Keyboard::Left;
        m_keymap["right"] = sf::Keyboard::Right;
        m_keymap["shoot"] = sf::Keyboard::Space;
        m_keymap["speedup"] = sf::Keyboard::X;
    }
}
