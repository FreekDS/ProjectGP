#ifndef ROADFIGHTER_SFML_PLAYER_H
#define ROADFIGHTER_SFML_PLAYER_H

#include <memory>
#include <GLL/Player.h>
#include <SFML/Graphics.hpp>

using namespace std;

using window_ptr = shared_ptr<sf::RenderWindow>;

namespace RoadFighterSFML {

    /**
     * This class is the SFML implementation of Player
     * A SFML player has:
     * - All features of a normal player
     * - A texture
     * - A sprite
     * - A shared pointer to a SFML window
     */
    class Player : public RoadFighter::Player {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        window_ptr m_window;
    public:
        /**
         * Constructor for SFML Player
         * m_texture is taken from m_sprite
         * @param sprite Sprite of the player
         * @param window RenderWindow to be drawn on
         */
        Player(const sf::Sprite& sprite, const window_ptr& window);

        /**
         * Constructor for SFML Player
         * This constructor will look for file_name in the res/sprites/entity folder
         * @param file_name File name of .png image
         * @param window RenderWindow to be drawn on
         */
        Player(const std::string& file_name, const window_ptr& window);

        /**
         * Default destructor for SFML Player
         */
        ~Player() override;

        /**
         * Updates the screen coordinates of the sprite based on the coordinates in the Game Logic
         * This method makes use of the @see Transformation class
         */
        void updateSpriteLocation() override;

        /**
         * Virtual function to draw the entity
         */
        void draw() const override;

        /**
         * Virtual function to update the entity
         * - Resets the rotation of the sprite
         */
        void update() override;

        /**
         * Sets the rotation of the sprite
         * @param angle The angle over which the sprite needs to be rotated
         */
        void setSpriteRotation(float angle);
    };

} // namespace RoadFighterSFML

#endif //ROADFIGHTER_SFML_PLAYER_H
