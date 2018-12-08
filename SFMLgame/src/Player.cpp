#include <GLL/Transformation.h>
#include <Player.h>

namespace RoadFighterSFML {

    Player::Player(const sf::Sprite& sprite, window_ptr& window)
            :m_texture(*sprite.getTexture()), m_sprite(sprite), m_window(window)
    {
        m_sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
        updateSpriteLocation();
    }

    Player::Player(const std::string& file_name, window_ptr& window)
            :m_window(window)
    {
        string path = "./res/sprites/entity/";
        m_texture.loadFromFile(path + file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        // todo scale correctly
        m_sprite.scale(5,5);
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


    Player::~Player() = default;


} // RoadFighterSFML