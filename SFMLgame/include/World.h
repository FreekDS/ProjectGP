#ifndef ROADFIGHTER_SFML_WORLD_H
#define ROADFIGHTER_SFML_WORLD_H

#include <GLL/World.h>
#include <SFML/Graphics.hpp>
#include "Player.h"

using keymap = map<string, sf::Keyboard::Key>;

namespace RoadFighterSFML {

    /**
     * This class is the SFML implementation of a World.
     * A SFML World has:
     * - The same features as a World.
     * - Two sprites of the same texture to represent the infinite background.
     * - A background texture.
     * - A shared pointer to an SFML window.
     * - A keymap which contains the controls.
     * - A boolean to determine whether the game is in debug mode or not.
     */
    class World : public RoadFighter::World {
    private:
        sf::Sprite m_sprite;
        sf::Sprite m_sprite2;
        sf::Texture m_texture;
        window_ptr m_window;
        keymap m_keymap;
        bool m_debug;
    public:
        /**
         * Constructor for the SFML World.
         * This constructor will look for file_name in the folder "./res/sprites/ui/".
         * @param file_name Name of the file of the background.
         * @param window Reference to the SFML window.
         * @param debug Enable or disable debug information.
         */
        World(const string& file_name, window_ptr& window, bool debug = false);

        /**
         * Draws the world and its components to the window.
         */
        void draw() const override;


        /**
         * Reads the user input and interprets them.
         */
        void readInput() override;

        /**
         * Initializes the keymap.
         */
        void initializeKeymap();

        /**
         * Updates the background loop.
         * The background loop works as follows: there are two equal sprites pasted above each other.
         * When one sprite leaves the window completely (is not visible anymore) This one is moved above.
         * the one which is still visible to create a notion of an infinite scrolling background.
         * @param toMove The sprite which is not visible on the screen.
         * @param other The other sprite.
         *
         * If toMove is visible, and other is not, both sprites are swapped.
         */
        void backgroundLoopUpdate(sf::Sprite& toMove, sf::Sprite& other);

        /**
         * Draws the colliders of an entity.
         * @param entity Entity to draw colliders of.
         */
        void drawColliders(const shared_ptr<RoadFighter::Entity>& entity) const;

        /**
         * Draws the boundaries of the world (great for debugging).
         */
        void drawBounds() const;

        /**
         * This overridden function does nothing with the world.
         */
        void updateSpriteLocation() override {}

        /**
         * Returns a shared pointer of this World.
         * @return Shared pointer of this world.
         */
        shared_ptr<RoadFighter::World> getPtr() override;
    };

}

#endif //ROADFIGHTER_SFML_WORLD_H
