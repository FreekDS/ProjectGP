#include <GLL/FinishLine.h>

namespace RoadFighter {

    FinishLine::FinishLine(const shared_ptr<World>& world)
    {
        double width = world->getRightBoundary() - world->getLeftBoundary();
        double height = 1.0/3.0 * width;
        initializeCorners(width, height);
        setPos(0.3, 2.8);
        setType(FINISH);
    }

    void FinishLine::update()
    {
        updateSpriteLocation();
    }

    bool FinishLine::canBeDestroyed() const
    {
        return false;
    }

    void FinishLine::draw() const
    {

    }

    void FinishLine::updateSpriteLocation()
    {

    }

}
