#include <RacingCar.h>
#include <Utilities.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    RacingCar::RacingCar(const string& file_name, const window_ptr& window, const shared_ptr<RoadFighter::World>& world,
            const shared_ptr<RoadFighter::Player>& player)
            :RoadFighter::RacingCar(player, world), m_window(window)
    {
        string path = "./res/sprites/entity/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = std::move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        scaleSprite(m_sprite, getUpperLeftCorner(), getBottomRightCorner());
    }

    void RacingCar::draw() const
    {
        m_window->draw(m_sprite);
    }

    void RacingCar::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    void RacingCar::rotateSprite(float angle)
    {
        m_sprite.rotate(angle);
    }

    void RacingCar::setSpriteRotation(float angle)
    {
        m_sprite.setRotation(angle);
    }

} // namespace RoadFigherSFML