#include <GLL/FinishLine.h>

namespace RoadFighter {

    /**
     * Constructor of the FinishLine.
     * Initializes the width of the finish line based on the world borders.
     * Initializes the corners of the finish line.
     * Initializes the position of the finish line.
     * @param world Shared pointer to the world.
     */
    FinishLine::FinishLine(const shared_ptr<World>& world)
    {
        double width = world->getRightBoundary()-world->getLeftBoundary();
        double height = 1.0/3.0*width;
        initializeCorners(width, height);
        setPos(0.3, 2.8);
        setType(FINISH);
    }

    /**
     * Check whether the finish line can be destroyed or not.
     * @return False
     */
    bool FinishLine::canBeDestroyed() const
    {
        return false;
    }


} // namespace RoadFighter
