#ifndef ROADFIGHTER_SFML_ENTITYFACTORY_H
#define ROADFIGHTER_SFML_ENTITYFACTORY_H

#include <GLL/EntityFactory.h>
#include <GLL/World.h>
#include <SFML/Graphics.hpp>

using window_ptr = shared_ptr<sf::RenderWindow>;

namespace RoadFighterSFML {

    /**
     * This class is an Abstract Entity factory for the SFML objects
     * of the world.
     * This class is derived from EntityFactory and has:
     * - a pointer to a SFML window.
     */
    class EntityFactory : public RoadFighter::EntityFactory {
    private:
        window_ptr m_window;
    public:

        /**
         * Constructor of EntityFactory.
         * @param window Const reference to the SFML window.
         */
        explicit EntityFactory(const window_ptr& window);

        /**
         * Destructor of EntityFactory.
         */
        virtual ~EntityFactory();

        /**
         * This function creates a Player.
         * A player needs a speed observer, which is constructed in this function as well.
         * @return Shared pointer to an entity (= the player).
         */
        shared_ptr<RoadFighter::Entity> createPlayer() const override;

        /**
         * This function creates a Passing Car.
         * @param world Shared pointer to the world.
         * @param player Shared pointer to the player.
         * @return Shared pointer to an entity (= the passing car)
         */
        shared_ptr<RoadFighter::Entity> createPassingCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const override;

        /**
         * This function creates a Race car.
         * @param world Shared pointer to the world.
         * @param player Shared pointer to the player.
         * @return Shared pointer to an entity (= race car)
         */
        shared_ptr<RoadFighter::Entity> createRaceCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const override;

        /**
         * This function creates a bullet.
         * @param world
         * @param player
         * @return
         */
        shared_ptr<RoadFighter::Entity> createBullet(const RoadFighter::Position& playerPos, double playerHeight) const override;
    };

} // namespace RoadFighterSFML

#endif //ROADFIGHTER_SFML_ENTITYFACTORY_H
