#include <Bullet.h>
#include <GLL/Transformation.h>
#include <Utilities.h>

namespace RoadFighterSFML {

    /**
     * Draws the Bullet to the screen.
     */
    void Bullet::draw() const
    {
        m_window->draw(m_sprite);
    }

    /**
     * Updates the location of the sprite.
     */
    void Bullet::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    Bullet::Bullet(const string& file_name, double shootSpeed, const RoadFighter::Position& playerPos,
            double playerHeight,
            const shared_ptr<sf::RenderWindow>& m_window)
            :RoadFighter::Bullet(shootSpeed, playerPos, playerHeight), m_window(m_window)
    {
        string path = "./res/sprites/object/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = std::move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        scaleSprite(m_sprite, getUpperLeftCorner(), getBottomRightCorner());
        updateSpriteLocation();
    }


} // namespace RoadFighterSFML