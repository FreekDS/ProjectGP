#include <RacingCar.h>
#include <Utilities.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    /**
     * Constructor for RacingCar.
     * @param file_name File name of the texture. This function looks in the folder "./res/sprites/entity/".
     * @param window A shared pointer to the window.
     * @param world A shared pointer to the world.
     * @param player A shared pointer to the player
     */
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

    /**
     * Draws the Racing car to the screen.
     */
    void RacingCar::draw() const
    {
        m_window->draw(m_sprite);
    }

    /**
     * Updates the location of the sprite.
     */
    void RacingCar::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    /**
     * Rotates the sprite relative to its current rotation.
     * @param angle Angle to rotate over.
     */
    void RacingCar::rotateSprite(float angle)
    {
        m_sprite.rotate(angle);
    }

    /**
     * Sets the absolute rotation of the sprite.
     * @param angle Angle to rotate.
     */
    void RacingCar::setSpriteRotation(float angle)
    {
        m_sprite.setRotation(angle);
    }

} // namespace RoadFigherSFML