#ifndef ROADFIGHTER_SFML_PLAYER_H
#define ROADFIGHTER_SFML_PLAYER_H

#include <memory>
#include "GLL/Player.h"
#include "SFML/Graphics.hpp"

using namespace std;

namespace RoadFighterSFML {

    /**
     * With SFML visually representable Player
     */
    class Player : public RoadFighter::Player {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        shared_ptr<sf::RenderWindow> m_window;
    public:
        /**
         * Constructor for SFML Player
         * m_texture is taken from m_sprite
         * @param sprite Sprite of the player
         * @param window RenderWindow to be drawn on
         */
        Player(const sf::Sprite& sprite, shared_ptr<sf::RenderWindow>& window);

        /**
         * Constructor for SFML Player
         * This constructor will look for file_name in the res/sprites/entity folder
         * @param file_name File name of .png image
         * @param window RenderWindow to be drawn on
         */
        Player(const std::string& file_name, shared_ptr<sf::RenderWindow>& window);

        /**
         * Default destructor for SFML Player
         */
        ~Player() override;


        /**
         * Updates the screen coordinates of the sprite based on the coordinates in the Game Logic
         * This method makes use of the @see Transformation class
         */
        void updateSpriteLocation();

        /**
         * This function makes the Player visible to the screen
         */
        void draw() const override;

        void update() override;
    };

}

#endif //ROADFIGHTER_SFML_PLAYER_H
