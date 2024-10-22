#include <EntityFactory.h>
#include <Player.h>
#include <RacingCar.h>
#include <PassingCar.h>
#include <Observer.h>
#include <Bullet.h>


namespace RoadFighterSFML {

    /**
     * This function creates a Player.
     * A player needs a speed observer, which is constructed in this function as well.
     * @return Shared pointer to an entity (= the player).
     */
    shared_ptr<RoadFighter::Entity> EntityFactory::createPlayer() const
    {
        auto player = make_shared<Player>("player_car.png", m_window);
        auto speedObserver = make_shared<SpeedObserver>(player, "Speed: ", m_window);
        auto distanceObserver = make_shared<RoadFighter::DistanceObserver>(player);
        auto scoreObserver = make_shared<ScoreObserver>(player, "Score: ", m_window);
        player->attach(speedObserver);
        player->attach(distanceObserver);
        player->attach(scoreObserver);
        return player;
    }

    /**
     * This function creates a Passing Car.
     * @param world Shared pointer to the world.
     * @param player Shared pointer to the player.
     * @return Shared pointer to an entity (= the passing car)
     */
    shared_ptr<RoadFighter::Entity>
    EntityFactory::createPassingCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const
    {
        auto passingCar = make_shared<PassingCar>("passing_car.png", m_window, world, player);
        return passingCar;
    }

    /**
     * This function creates a Race car.
     * @param world Shared pointer to the world.
     * @param player Shared pointer to the player.
     * @return Shared pointer to an entity (= race car)
     */
    shared_ptr<RoadFighter::Entity> EntityFactory::createRaceCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const
    {
        auto racingCar = make_shared<RacingCar>("racing_car.png", m_window, world, player);
        return racingCar;
    }

    shared_ptr<RoadFighter::Entity> EntityFactory::createBullet(const RoadFighter::Position& playerPos, double playerHeight) const
    {
        auto bullet = make_shared<Bullet>("bullet.png", 0.06, playerPos, playerHeight, m_window);
        return bullet;
    }

    /**
     * Destructor of EntityFactory.
     */
    EntityFactory::~EntityFactory() = default;

    /**
     * Constructor of EntityFactory.
     * @param window Const reference to the SFML window.
     */
    EntityFactory::EntityFactory(const window_ptr& window)
            :m_window(window) { }


} // namespace RoadFighterSFML
