#ifndef ROADFIGHTER_SFML_FINISHLINE_H
#define ROADFIGHTER_SFML_FINISHLINE_H

#include <GLL/FinishLine.h>
#include <GLL/World.h>
#include <SFML/Graphics.hpp>

namespace RoadFighterSFML {

    class FinishLine : public RoadFighter::FinishLine {
    private:
        shared_ptr<sf::RenderWindow> m_window;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        FinishLine(const string& file_name, const shared_ptr<RoadFighter::World>& world,
                const shared_ptr<sf::RenderWindow>& window);

        void draw() const override;

        void updateSpriteLocation() override;
    };

}

#endif //ROADFIGHTER_SFML_FINISHLINE_H
