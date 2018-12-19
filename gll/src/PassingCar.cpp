#include <utility>

#include <GLL/PassingCar.h>
#include <GLL/Transformation.h>
#include <GLL/Random.h>

namespace RoadFighter {

    PassingCar::PassingCar(double speed, const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :Vehicle(speed), m_player(player), m_world(world)
    {
        double width = 0.24;
        double height = 0.40;
        initializeCorners(width, height);
        initializePosition();
    }

    void PassingCar::update()
    {

    }

    /**
     * Determine whether the PassingCar can be destroyed or not.
     * A PassingCar can be destroyed if it's Y position is lower than 2 times the minimum Y
     * or if it's Y position is greater than 2 times the maximum Y.
     * This minimum and maximum are obtained from @see Transformation
     * @return True if the PassingCar can be destroyed
     */
    bool PassingCar::canBeDestroyed() const
    {
        auto trans = Transformation::getInstance();
        range yRange = trans->getYRange();
        return getPos().y<2*yRange.first || getPos().y>2*yRange.second;
    }

    void PassingCar::moveUp()
    {

    }

    void PassingCar::moveDown()
    {

    }

    PassingCar::~PassingCar() = default;

    PassingCar::PassingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :m_player(player), m_world(world) { }

    void PassingCar::initializePosition()
    {
        auto rand = Random::getInstance();
        auto trans = Transformation::getInstance();

        // Add 1/2 of the width so we cannot spawn before the left boundary
        double minPos = m_world->getLeftBoundary() + getWidth()/2;
        // Remove 1/2 of the width so we cannot spawn further than the right boundary
        double maxPos = m_world->getRightBoundary() - getWidth()/2;

        double yPos = trans->getYRange().second + getWidth();
        double xPos = rand->randDouble(minPos, maxPos);

        setPos(xPos, yPos);
    }

} // namespace RoadFighter
