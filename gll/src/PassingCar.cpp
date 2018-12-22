#include <utility>

#include <GLL/PassingCar.h>
#include <GLL/Transformation.h>
#include <GLL/Random.h>

namespace RoadFighter {

    /**
     * Constructor of PassingCar taking the speed of the vehicle.
     * @param speed Speed of the vehicle.
     * @param player Shared pointer to the Player.
     * @param world Shared pointer to the world.
     */
    PassingCar::PassingCar(double speed, const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :Vehicle(speed), m_player(player), m_world(world)
    {
        double width = 0.24;
        double height = 0.40;
        initializeCorners(width, height);
        initializePosition();
        auto rand = Random::getInstance();
        setMoveSpeed(rand->randDouble(m_player->getMovespeed()/5, m_player->getMovespeed()*1.5));
    }

    /**
     * Updates the PassingCar.
     */
    void PassingCar::update()
    {
        if(m_player->getSpeed() < getSpeed())
            moveUp();
        else
            moveDown();
    }

    /**
     * Determine whether the PassingCar can be destroyed or not.
     * A PassingCar can be destroyed if it's Y position is lower than 2 times the minimum Y
     * or if it's Y position is greater than 2 times the maximum Y.
     * A PassingCar can also be destroyed if it has crashed.
     * This minimum and maximum are obtained from @see Transformation
     * @return True if the PassingCar can be destroyed
     */
    bool PassingCar::canBeDestroyed() const
    {
        auto trans = Transformation::getInstance();
        range yRange = trans->getYRange();
        return getPos().y<2*yRange.first || getPos().y>2*yRange.second || hasCrashed();
    }

    /**
     * Moves the PassingCar up on the screen.
     */
    void PassingCar::moveUp()
    {
        updatePos(0, getMovespeed());
    }

    /**
     * Moves the PassingCar down on the screen.
     */
    void PassingCar::moveDown()
    {
        updatePos(0, -getMovespeed());
    }

    /**
     * Default destructor of PassingCar.
     */
    PassingCar::~PassingCar() = default;

    /**
     * Constructor of PassingCar taking the Player and World as parameter.
     * @param player Shared pointer to the Player.
     * @param world Shared pointer to the World.
     */
    PassingCar::PassingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :m_player(player), m_world(world)
    {
        double width = 0.24;
        double height = 0.40;
        initializeCorners(width, height);
        initializePosition();
        auto rand = Random::getInstance();
        setMoveSpeed(rand->randDouble(m_player->getMovespeed()/5, m_player->getMovespeed()*1.5));
    }

    /**
     * Initializes the position randomly inside the World.
     * The position will be initialized in between the two boundaries of the World.
     */
    void PassingCar::initializePosition()
    {
        auto rand = Random::getInstance();
        auto trans = Transformation::getInstance();

        // Add 1/2 of the width so we cannot spawn before the left boundary
        double minPos = m_world->getLeftBoundary()+getWidth()/2;
        // Remove 1/2 of the width so we cannot spawn further than the right boundary
        double maxPos = m_world->getRightBoundary()-getWidth()/2;

        double yPos = trans->getYRange().second+getWidth();
        double xPos = rand->randDouble(minPos, maxPos);

        setPos(xPos, yPos);
    }

} // namespace RoadFighter
