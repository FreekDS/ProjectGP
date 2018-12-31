#include "GLL/Game.h"

namespace RoadFighter {

    /**
     * Constructor for Game.
     * @param world Const reference to world of the game.
     */
    Game::Game(const shared_ptr<World>& world)
            :m_world(world) { }

    /**
     * Default constructor of Game.
     * This constructor initializes the World as a nullptr.
     */
    Game::Game()
            :m_world(nullptr) { }

    /**
     * Default destructor of Game.
     */
    Game::~Game() = default;

} // namespace RoadFighter


