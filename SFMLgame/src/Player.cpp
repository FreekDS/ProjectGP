#include <GLL/Transformation.h>
#include <Utilities.h>
#include <Player.h>

namespace RoadFighterSFML {

    /**
     * Constructor for SFML Player.
     * m_texture is taken from m_sprite.
     * @param sprite Sprite of the player.
     * @param window RenderWindow to be drawn on.
     */
    Player::Player(const sf::Sprite& sprite, const window_ptr& window)
            :m_texture(*sprite.getTexture()), m_sprite(sprite), m_window(window)
    {
        m_sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
        updateSpriteLocation();
    }

    /**
     * Constructor for SFML Player.
     * This constructor will look for file_name in the res/sprites/entity folder.
     * @param file_name File name of .png image.
     * @param window RenderWindow to be drawn on.
     */
    Player::Player(const std::string& file_name, const window_ptr& window)
            :m_window(window)
    {
        string path = "./res/sprites/entity/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        scaleSprite(m_sprite, getUpperLeftCorner(), getBottomRightCorner());
        updateSpriteLocation();
    }

    /**
     * Virtual function to draw the entity.
     */
    void Player::draw() const
    {
        m_window->draw(m_sprite);
        for(const shared_ptr<RoadFighter::Observer>& obs : m_observers)
            obs->draw();
    }

    /**
     * Updates the screen coordinates of the sprite based on the coordinates in the Game Logic.
     * This method makes use of the @see Transformation class.
     */
    void Player::updateSpriteLocation()
    {
        shared_ptr<RoadFighter::Transformation> trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position screenPos = trans->getScreenCoordinate(this->getPos().x, this->getPos().y);
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
    }

    /**
     * Sets the absolute rotation of the sprite.
     * @param angle The angle over which the sprite needs to be rotated.
     */
    void Player::setSpriteRotation(float angle)
    {
        m_sprite.setRotation(angle);
    }

    /**
     * Rotates the sprite relative to its previous rotation.
     * @param angle Angle over which the sprite needs to be rotated.
     */
    void Player::rotateSprite(float angle)
    {
        m_sprite.rotate(angle);
    }

    /**
     * Default destructor for SFML Player.
     */
    Player::~Player() = default;


} // namespace RoadFighterSFML