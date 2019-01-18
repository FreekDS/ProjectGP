#ifndef ROADFIGHTER_SFML_BULLET_H
#define ROADFIGHTER_SFML_BULLET_H

#include <GLL/Bullet.h>
#include <SFML/Graphics.hpp>
#include <memory>

namespace RoadFighterSFML {

    /**
     * This class is the SFML implementation of the Bullet class
     */
    class Bullet : public RoadFighter::Bullet {
    private:
        shared_ptr<sf::RenderWindow> m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:

        Bullet(const string& file_name, double shootSpeed, const RoadFighter::Position& playerPos, double playerHeight,
                const shared_ptr<sf::RenderWindow>& m_window);

        /**
         * Draws the bullet to the screen.
         */
        void draw() const override;

        /**
         * Updates the location of the sprite.
         */
        void updateSpriteLocation() override;
    };

}

#endif //ROADFIGHTER_SFML_BULLET_H
