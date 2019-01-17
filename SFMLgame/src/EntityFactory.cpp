#include <EntityFactory.h>
#include <Player.h>
#include <RacingCar.h>
#include <PassingCar.h>
#include <Observer.h>
#include <FinishLine.h>

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
        player->attach(speedObserver);
        player->attach(distanceObserver);
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

    shared_ptr<RoadFighter::Entity> EntityFactory::createRaceCar(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const
    {
        auto racingCar = make_shared<RacingCar>("racing_car.png", m_window, world, player);
        return racingCar;
    }

    shared_ptr<RoadFighter::Entity> EntityFactory::createBullet(shared_ptr<RoadFighter::World> world, shared_ptr<RoadFighter::Player> player) const
    {
        return shared_ptr<RoadFighter::Entity>();
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

    shared_ptr<RoadFighter::Entity> EntityFactory::createFinishLine(const shared_ptr<RoadFighter::World>& world) const
    {
        auto finish = make_shared<RoadFighter::FinishLine>(world);
        return finish;
    }

} // namespace RoadFighterSFML
