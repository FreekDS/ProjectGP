
#include <Player.h>
#include <GLL/Transformation.h>

#include "Player.h"

namespace RoadFighterSFML {

    Player::Player(const sf::Sprite& sprite, shared_ptr<sf::RenderWindow>& window)
            :m_texture(*sprite.getTexture()), m_sprite(sprite), m_window(window)
    {
        m_sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
        updateSpriteLocation();
    }

    Player::Player(const std::string& file_name, shared_ptr<sf::RenderWindow>& window)
            :m_window(window)
    {
        std::string path = "./res/sprites/entity/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = sprite;
        updateSpriteLocation();
    }

    void Player::draw() const
    {
        m_window->draw(m_sprite);
    }

    void Player::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    void Player::update()
    {

    }

    bool Player::canBeDestroyed()
    {
        return false;
    }

    Player::~Player() = default;


} // RoadFighterSFML