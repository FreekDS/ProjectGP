#ifndef ROADFIGHTER_SFML_RACINGCAR_H
#define ROADFIGHTER_SFML_RACINGCAR_H

#include <GLL/RacingCar.h>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

    using window_ptr = shared_ptr<sf::RenderWindow>;

    /**
     * This class is the SFML implementation of a Racing Car.
     * A Racing car has:
     * - A pointer to a window.
     * - A texture.
     * - A sprite.
     */
    class RacingCar : public RoadFighter::RacingCar {
    private:
        window_ptr m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        /**
         * Constructor for RacingCar.
         * @param file_name File name of the texture. This function looks in the folder "./res/sprites/entity/".
         * @param window A shared pointer to the window.
         * @param world A shared pointer to the world.
         * @param player A shared pointer to the player
         */
        RacingCar(const string& file_name, const window_ptr& window, const shared_ptr<RoadFighter::World>& world,
                const shared_ptr<RoadFighter::Player>& player);

        /**
         * Draws the Racing car to the screen.
         */
        void draw() const override;

        /**
         * Updates the location of the sprite.
         */
        void updateSpriteLocation() override;

        /**
         * Rotates the sprite relative to its current rotation.
         * @param angle Angle to rotate over.
         */
        void rotateSprite(float angle) override;

        /**
         * Sets the absolute rotation of the sprite.
         * @param angle Angle to rotate.
         */
        void setSpriteRotation(float angle) override;

    };

}

#endif //ROADFIGHTER_SFML_RACINGCAR_H
