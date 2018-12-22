#include <World.h>
#include <Utilities.h>
#include <GLL/Transformation.h>
#include <iostream>

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
            if(m_debug) {
                drawColliders(entity);
                drawBounds();
            }
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
    World::World(const string& file_name, window_ptr& window, bool debug)
            :m_window(window), m_debug(debug)
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
        scaleSprite(m_sprite, getBottomRightCorner(), getUpperLeftCorner());

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
        shared_ptr<Player> player = dynamic_pointer_cast<Player>(getPlayer());
        if (sf::Keyboard::isKeyPressed(m_keymap["up"])) {
            // move player up
            player->moveUp();
            player->updateSpriteLocation();

        }
        if (sf::Keyboard::isKeyPressed(m_keymap["down"])) {
            // move player down
            player->moveDown();
            player->updateSpriteLocation();
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["left"])) {
            // move player left
            player->moveLeft(getLeftBoundary());
            player->updateSpriteLocation();
            if(player->isMoving())
                player->setSpriteRotation(-10);
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["right"])) {
            // move player right
            player->moveRight(getRightBoundary());
            player->updateSpriteLocation();
            if(player->isMoving())
                player->setSpriteRotation(10);
        }
        if (sf::Keyboard::isKeyPressed(m_keymap["shoot"])) {
            // let player shoot a bullet

        }
        if (sf::Keyboard::isKeyPressed(m_keymap["speedup"])) {
            // player accelerates
            player->accelerate();
        }
        if(!sf::Keyboard::isKeyPressed(m_keymap["speedup"])){
            player->slowDown();
        }

        m_sprite.move(0, static_cast<float>(player->getSpeed()));
        m_sprite2.move(0, static_cast<float>(player->getSpeed()));
        backgroundLoopUpdate(m_sprite2, m_sprite);
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

    /**
     * Draws the colliders of an entity
     * @param entity Entity to draw colliders of
     */
    void World::drawColliders(const shared_ptr<RoadFighter::Entity>& entity) const
    {
        for(const RoadFighter::BoxCollider& collider : entity->getColliders()){
            sf::RectangleShape rectangle;
            pair<float, float> collSize = getSFMLSize(collider.getUpperLeftCorner(), collider.getBottomRightCorner());
            sf::Vector2f size(collSize.first, collSize.second);
            rectangle.setSize(size);
            rectangle.setOutlineThickness(1.5f);
            rectangle.setFillColor(sf::Color::Transparent);
            if(entity->isPlayer())
                rectangle.setOutlineColor(sf::Color::Blue);
            else
                rectangle.setOutlineColor(sf::Color::Green);
            rectangle.setOrigin(rectangle.getGlobalBounds().width /2, rectangle.getGlobalBounds().height/2);
            auto trans = RoadFighter::Transformation::getInstance();
            RoadFighter::Position screenPos = trans->getScreenCoordinate(collider.getCenter());
            rectangle.setPosition(static_cast<float>(screenPos.x), static_cast<float>(screenPos.y));
            m_window->draw(rectangle);
        }
    }

    /**
     * Draws the boundaries of the world (great for debugging)
     */
    void World::drawBounds() const
    {
        sf::RectangleShape bound1;
        bound1.setFillColor(sf::Color::Red);
        sf::Vector2f size(5, m_window->getSize().y);
        bound1.setSize(size);
        sf::RectangleShape bound2 = bound1;
        auto trans = RoadFighter::Transformation::getInstance();
        RoadFighter::Position posBound1(getRightBoundary(), 0);
        RoadFighter::Position posBound2(getLeftBoundary(), 0);
        RoadFighter::Position screenPos1 = trans->getScreenCoordinate(posBound1);
        RoadFighter::Position screenPos2 = trans->getScreenCoordinate(posBound2);
        bound1.setPosition(static_cast<float>(screenPos1.x), 0);
        bound2.setPosition(static_cast<float>(screenPos2.x), 0);
        m_window->draw(bound1);
        m_window->draw(bound2);
    }

    /**
     * Returns a shared pointer of this World.
     * @return Shared pointer of this world.
     */
    shared_ptr<RoadFighter::World> World::getPtr()
    {
        return shared_from_this();
    }

} // namespace RoadFighter
