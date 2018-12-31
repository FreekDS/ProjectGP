#include <PassingCar.h>
#include <GLL/Transformation.h>
#include <Utilities.h>
#include <iostream>

namespace RoadFighterSFML {

    /**
     * Constructor for PassingCar.
     * @param file_name File name of texture. Looks in the folder "./res/sprites/entity/".
     * @param window Shared pointer to the window.
     * @param world Shared pointer to the world.
     * @param player Shared pointer to the Player.
     */
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

    /**
     * Draws the passing car to the window.
     */
    void PassingCar::draw() const
    {
        m_window->draw(m_sprite);
    }

    /**
     * Updates the location of the sprite.
     */
    void PassingCar::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    /**
     * Rotates the sprite relative to its current rotation.
     * @param angle Angle to rotate over.
     */
    void PassingCar::rotateSprite(float angle)
    {
        m_sprite.rotate(angle);
    }


} // namespace RoadFighterSFML