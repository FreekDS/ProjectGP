#include <GLL/EntityFactory.h>
#include <GLL/FinishLine.h>

namespace RoadFighter {

    /**
     * This function creates a finishLine.
     * @param world Shared pointer to the world.
     * @return Shared pointer to the finish line.
     */
    shared_ptr<Entity> EntityFactory::createFinishLine(const shared_ptr<RoadFighter::World>& world) const
    {
        auto finish = make_shared<FinishLine>(world);
        return finish;
    }

} // namespace RoadFighter
