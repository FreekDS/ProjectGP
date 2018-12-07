#include "GLL/Game.h"

namespace RoadFighter{

    Game::Game(const shared_ptr<World>& world)
            :m_world(world) { }

    Game::Game() : m_world(nullptr) { }
}


