#ifndef ROADFIGHTER_SFML_RACINGCAR_H
#define ROADFIGHTER_SFML_RACINGCAR_H

#include <GLL/RacingCar.h>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

    using window_ptr = shared_ptr<sf::RenderWindow>;

    /**
     * This class is the SFML implementation of a Racing Car
     */
    class RacingCar : public RoadFighter::RacingCar {
    private:
        window_ptr m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        RacingCar(const string& file_name, const window_ptr& window, const shared_ptr<RoadFighter::World>& world,
                const shared_ptr<RoadFighter::Player>& player);

        void draw() const override;

        void updateSpriteLocation() override;

        void rotateSprite(float angle) override;

        void setSpriteRotation(float angle) override;

    };

}

#endif //ROADFIGHTER_SFML_RACINGCAR_H
