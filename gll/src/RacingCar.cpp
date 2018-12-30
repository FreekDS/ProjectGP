#include <GLL/RacingCar.h>
#include <GLL/Random.h>
#include <GLL/Transformation.h>

namespace RoadFighter {

    /**
     * Initially, there are no racing cars.
     */
    unsigned int RacingCar::CAR_COUNT = 0;

    void RacingCar::accelerate()
    {
        auto rand = Random::getInstance();
        if (getSpeed()<m_range.second) {
            setSpeed(getSpeed()+rand->randDouble(1, 3));
        }
    }

    void RacingCar::slowDown()
    {
        auto rand = Random::getInstance();
        if (getSpeed()>m_range.first) {
            setSpeed(getSpeed()-rand->randDouble(1, 3));
        }
    }

    void RacingCar::moveLeft(double world_boundary)
    {
        if (isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(-getMovespeed(), 0);
            if (getUpperLeftCorner().x<world_boundary)
                updatePos(getMovespeed()+0.000001, 0);
        }
    }

    void RacingCar::moveRight(double world_boundary)
    {
        if (isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(getMovespeed(), 0);
            if (getBottomRightCorner().x>world_boundary)
                updatePos(-getMovespeed()-0.000001, 0);
        }
    }

    void RacingCar::moveUp()
    {
        updatePos(0, getMovespeed());
    }

    void RacingCar::moveDown()
    {
        updatePos(0, -getMovespeed());
    }

    /**
     * Updates the race car every game tick.
     *
     * First phase: the player has not started moving:
     * - We don't do anything, whenever the player starts moving, we move to phase two.
     *
     * Second phase: the player started moving, but the speed is lower than the minimum speed
     * - First we move the racing car up or down depending on the player's speed.
     * - We have to accelerate 100% of the time.
     * - If the speed is greater than the minimum, phase three starts.
     *
     * Third phase: the game is running normal
     * - Randomly accelerate
     * - Randomly slow down
     * - Update the move speed depending on the speed deficit with the player
     * - Randomly move left
     * - Randomly move right
     * - Move up or down depending on the player speed
     *
     * If the car finished the race, don't do anything.
     */
    void RacingCar::update()
    {
        if(hasFinished())
            return;

        auto rand = Random::getInstance();

        // First phase

        // initially the player is not moving and the car is not moving, so we do nothing.
        // The racing car starts updating whenever the player starts moving.
        if (m_player->getSpeed()==0 && getSpeed()==0)
            return;

        // Second phase

        // move up or down depending on the player's speed
        // The position of this statements is important. If they are not in this position, the
        // racing cars would not move up or down when the cars are speeding up for the first time.
        if (m_player->getSpeed()<getSpeed())
            moveUp();
        else
            moveDown();

        // when we move slower than the minimum speed, we have to accelerate.
        if (getSpeed()<m_range.first) {
            accelerate();
            return;
        }

        // Third phase

        // accelerate or slow down randomly if possible
        if (rand->randInt(0, 100)<80)   // 80% chance
            accelerate();


        if (rand->randInt(0, 100)<20) // 20% chance
            slowDown();

        updateMoveSpeed();

        // move left or right randomly if possible
        if (rand->randInt(0, 100)<50)   // 50% chance
            moveLeft(m_world->getLeftBoundary());
        if (rand->randInt(0, 100)<50)    // 50% chance
            moveRight(m_world->getRightBoundary());
    }

    bool RacingCar::canBeDestroyed() const
    {
        return false;
    }

    RacingCar::RacingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :m_player(player), m_world(world)
    {
        double width = 0.24;
        double height = 0.40;
        double maxPlayer = player->getMaxSpeed(true);
        m_range.first = maxPlayer*1/3;
        m_range.second = maxPlayer*1.5;
        initializeCorners(width, height);
        initializePosition();
        setMoveSpeed(3.6);
        CAR_COUNT++;
    }

    RacingCar::~RacingCar()
    {
        CAR_COUNT--;
    }

    void RacingCar::initializePosition()
    {
        if (CAR_COUNT==0)
            setPos(0, 0);
        else if (CAR_COUNT==1) {
            setPos(0, 0);
        }
        else if (CAR_COUNT==2) {
            setPos(0, 0);
        }
        else if (CAR_COUNT==3) {
            setPos(0, 0);
        }
        else if (CAR_COUNT==4) {
            setPos(0, 0);
        }
        else
            throw runtime_error("Too much racing cars created... (Created "+to_string(CAR_COUNT+1)
                    +" but there are only 5 allowed)");
    }

    void RacingCar::finish()
    {
        m_finished = true;
    }

    bool RacingCar::hasFinished() const
    {
        return m_finished;
    }

    void RacingCar::updateMoveSpeed()
    {

    }

} // namespace RoadFighter
