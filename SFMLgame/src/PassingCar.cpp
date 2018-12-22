#include <PassingCar.h>
#include <GLL/Transformation.h>
#include <Utilities.h>
#include <iostream>

namespace RoadFighterSFML {

    PassingCar::PassingCar(const string& file_name, const window_ptr& window, shared_ptr<RoadFighter::World>& world,
            shared_ptr<RoadFighter::Player>& player)
            :RoadFighter::PassingCar(player, world), m_window(window)
    {
        string path = "./res/sprites/entity/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        scaleSprite(m_sprite, getUpperLeftCorner(), getBottomRightCorner());
    }

    void PassingCar::draw() const
    {
        m_window->draw(m_sprite);
    }

    void PassingCar::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }


} // namespace RoadFighterSFML