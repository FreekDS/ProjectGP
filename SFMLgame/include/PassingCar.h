#ifndef ROADFIGHTER_SFML_PASSINGCAR_H
#define ROADFIGHTER_SFML_PASSINGCAR_H

#include <GLL/PassingCar.h>
#include <GLL/World.h>
#include <GLL/Player.h>
#include <SFML/Graphics.hpp>

using window_ptr = shared_ptr<sf::RenderWindow>;

namespace RoadFighterSFML {

    /**
     * This class is the SFML implementation of a Passing Car.
     * A passing car has:
     * - A pointer to the window0
     * - A texture.
     * - A sprite.
     */
    class PassingCar : public RoadFighter::PassingCar {
    private:
        window_ptr m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        /**
         * Constructor for PassingCar.
         * @param file_name File name of texture. Looks in the folder "./res/sprites/entities/".
         * @param window Shared pointer to the window.
         * @param world Shared pointer to the world.
         * @param player Shared pointer to the Player.
         */
        PassingCar(const string& file_name, const window_ptr& window, shared_ptr<RoadFighter::World>& world, shared_ptr<RoadFighter::Player>& player);

        /**
         * Draws the passing car to the window.
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
    };
}

#endif //ROADFIGHTER_SFML_PASSINGCAR_H
