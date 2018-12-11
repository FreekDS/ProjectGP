#include <World.h>
#include <GLL/Transformation.h>

namespace RoadFighterSFML {

    /**
     * Draws the world and its components to the window
     */
    void World::draw() const
    {
        m_window->draw(m_sprite);
        m_window->draw(m_sprite2);
        for (const auto& entity : m_childEntities) {
            entity->draw();
        }
    }

    /**
     * Updates the world and all its components
     * This function first updates all the components
     * After that it will read the input with @see readInput()
     */
    void World::update()
    {
        for (const auto& entity : m_childEntities) {
            entity->update();
        }
        readInput();
    }

    /**
     * Constructor for the SFML World
     * This constructor will look for file_name in the folder ./res/sprites/ui/
     * This constructor will initialize the sprites and the texture and scale them so they match the window
     * The keymap will be initialized as well using @see initializeKeymap()
     * @param file_name Name of the file of the background
     * @param window Reference to the SFML window
     */
    World::World(const string& file_name, window_ptr& window)
            :m_window(window)
    {
        auto trans = RoadFighter::Transformation::getInstance();

        // Initialize sprite & texture
        string path = "./res/sprites/ui/";
        m_texture.loadFromFile(path+file_name);
        sf::Sprite sprite(m_texture);
        m_sprite = move(sprite);

        // Initialize position of sprite
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
        RoadFighter::Position screenPos = trans->getScreenCoordinate(getPos());
        m_sprite.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));

        // Scale sprite correctly depending on the screen size
        RoadFighter::Position screenUL = trans->getScreenCoordinate(getUpperLeftCorner());
        RoadFighter::Position screenBR = trans->getScreenCoordinate(getBottomRightCorner());
        double w = screenBR.x-screenUL.x;
        double h = screenBR.y-screenUL.y;
        float scaleX = static_cast<float>(w/m_texture.getSize().x);
        float scaleY = static_cast<float>(h/m_texture.getSize().y);
        m_sprite.scale(scaleX, scaleY);

        m_sprite2 = m_sprite;
        m_sprite2.setPosition(m_sprite2.getPosition().x,
                m_sprite2.getPosition().y-m_sprite2.getGlobalBounds().height+0.00001f);

        // Initialize controls
        initializeKeymap();
    }

    /**
     * Reads the user input and interprets them
     */
    void World::readInput()
    {
        if (sf::Keyboard::isKeyPressed(m_keymap["up"])) {
            // move player up
            shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
            player->moveUp();
            player->updateSpriteLocation();

        }
        if (sf::Keyboard::isKeyPressed(m_keymap["down"])) {
            // move player down
            shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
            player->moveDown();
            player->updateSpriteLocation();
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["left"])) {
            // move player left
            shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
            player->moveLeft(getLeftBoundary());
            player->updateSpriteLocation();
            player->setSpriteRotation(-8);
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["right"])) {
            // move player right
            shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
            player->moveRight(getRightBoundary());
            player->updateSpriteLocation();
            player->setSpriteRotation(8);
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["shoot"])) {
            // let player shoot a bullet

        }
        if (sf::Keyboard::isKeyPressed(m_keymap["speedup"])) {
            // player accelerates
            m_sprite.move(0, 0.8);
            m_sprite2.move(0, 0.8);
            backgroundLoopUpdate(m_sprite2, m_sprite);
        }

    }

    /**
     * Initializes the keymap
     */
    void World::initializeKeymap()
    {
        m_keymap["up"] = sf::Keyboard::Up;
        m_keymap["down"] = sf::Keyboard::Down;
        m_keymap["left"] = sf::Keyboard::Left;
        m_keymap["right"] = sf::Keyboard::Right;
        m_keymap["shoot"] = sf::Keyboard::Space;
        m_keymap["speedup"] = sf::Keyboard::X;
    }

    /**
     * Updates the background loop
     * The background loop works as follows: there are two equal sprites pasted above each other.
     * When one sprite leaves the window completely (is not visible anymore) This one is moved above
     * the one which is still visible to create a notion of an infinite scrolling background
     * @param toMove The sprite which is not visible on the screen
     * @param other The other sprite
     *
     * If toMove is visible, and other is not, both sprites are swapped
     */
    void World::backgroundLoopUpdate(sf::Sprite& toMove, sf::Sprite& other)
    {
        if (toMove.getPosition().y<other.getPosition().y)
            swap(toMove, other);
        if (toMove.getPosition().y-toMove.getGlobalBounds().height/2>m_window->getSize().y)
            toMove.setPosition(toMove.getPosition().x, other.getPosition().y-other.getGlobalBounds().height);
    }
}
