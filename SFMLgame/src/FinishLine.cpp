#include <FinishLine.h>
#include <Utilities.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    FinishLine::FinishLine(const string& file_name, const shared_ptr<RoadFighter::World>& world,
            const shared_ptr<sf::RenderWindow>& window)
            :RoadFighter::FinishLine(world), m_window(window)
    {
        string path = "./res/sprites/ui/";
//        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        scaleSprite(m_sprite, getUpperLeftCorner(), getBottomRightCorner());
    }

    void FinishLine::draw() const
    {
        m_window->draw(m_sprite);
    }

    void FinishLine::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

} // namespace RoadFighterSFML