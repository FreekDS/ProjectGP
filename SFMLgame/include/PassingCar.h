#ifndef ROADFIGHTER_SFML_PASSINGCAR_H
#define ROADFIGHTER_SFML_PASSINGCAR_H

#include <GLL/PassingCar.h>
#include <GLL/World.h>
#include <GLL/Player.h>
#include <SFML/Graphics.hpp>

using window_ptr = shared_ptr<sf::RenderWindow>;

namespace RoadFighterSFML {

    /**
     * This class is the SFML implemenation of a Passing Car
     */
    class PassingCar : public RoadFighter::PassingCar {
    private:
        window_ptr m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        PassingCar(const string& file_name, const window_ptr& window, shared_ptr<RoadFighter::World>& world, shared_ptr<RoadFighter::Player>& player);

        void draw() const override;

        void updateSpriteLocation() override;
    };
}

#endif //ROADFIGHTER_SFML_PASSINGCAR_H
