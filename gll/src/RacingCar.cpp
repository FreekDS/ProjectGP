#include <GLL/RacingCar.h>
#include <GLL/Random.h>
#include <GLL/Transformation.h>

namespace RoadFighter {

    /**
     * Initially, there are no racing cars.
     */
    unsigned int RacingCar::CAR_COUNT = 0;

    /**
     * Accelerates the racing car.
     */
    void RacingCar::accelerate()
    {
        auto rand = Random::getInstance();
        if (getSpeed()<m_range.second) {
            setSpeed(getSpeed()+rand->randDouble(1, 3));
        }
    }

    /**
     * Slows down the racing car.
     */
    void RacingCar::slowDown()
    {
        auto rand = Random::getInstance();
        if (getSpeed()>m_range.first) {
            setSpeed(getSpeed()-rand->randDouble(1, 3));
        }
    }

    /**
     * Moves the player to the left if possible.
     * @param world_boundary Left boundary of the world.
     */
    void RacingCar::moveLeft(double world_boundary)
    {
        if (isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(-getMovespeed(), 0);
            if (getUpperLeftCorner().x<world_boundary)
                updatePos(getMovespeed()+0.000001, 0);

            if (m_moveCooldown.timerFinished()) {
                m_lastMoveHorizontal = move::NONE;
                m_moveCooldown.setTimer(m_cooldownTime);
                m_moveCooldown.startTimer();
            }
            else {
                m_lastMoveHorizontal = move::LEFT;
            }
        }
    }

    /**
     * Moves the player to the right if possible.
     * @param world_boundary Right boundary of the world.
     */
    void RacingCar::moveRight(double world_boundary)
    {
        if (isMoving()) {
            auto trans = Transformation::getInstance();
            if (trans->isInGrid(getPos()))
                updatePos(getMovespeed(), 0);
            if (getBottomRightCorner().x>world_boundary)
                updatePos(-getMovespeed()-0.000001, 0);

            if (m_moveCooldown.timerFinished()) {
                m_lastMoveHorizontal = move::NONE;
                m_moveCooldown.setTimer(m_cooldownTime);
                m_moveCooldown.startTimer();
            }
            else {
                m_lastMoveHorizontal = move::RIGHT;
            }
        }
    }

    /**
     * Moves the race car up on the screen.
     */
    void RacingCar::moveUp()
    {
        auto trans = Transformation::getInstance();
        if (getPos().y<1.1*trans->getYRange().second)
            updatePos(0, getMovespeed());
    }

    /**
     * Moves the race car down on the screen.
     */
    void RacingCar::moveDown()
    {
        auto trans = Transformation::getInstance();
        if (getPos().y>4*trans->getYRange().first)
            updatePos(0, -getMovespeed());
    }

    /**
     * Updates the race car every game tick.
     * Updates the location of the sprite.
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
        updateSpriteLocation();
        if (hasFinished()) {
            disableColliders();
            return;
        }

        auto rand = Random::getInstance();
        if (!m_gameStarted && hasCrashed())
            repair(true);
        if (hasCrashed()) {
            setSpeed(0);
            if (!m_player->isMoving())
                setMoveSpeed(0);
            rotateSprite(10);
            if (repair()) {
                setPos(rand->randDouble(m_world->getLeftBoundary(), m_world->getRightBoundary()),
                        getPos().y);
            }
        }
        else {
            setSpriteRotation(0);
            setMoveSpeed(m_moveSpeed);
        }

        // First phase

        // initially the player is not moving and the car is not moving, so we do nothing.
        // The racing car starts updating whenever the player starts moving.
        if (m_player->getSpeed()==0 && getSpeed()==0 && !m_gameStarted)
            return;
        else
            m_gameStarted = true;
        // Second phase

        // move up or down depending on the player's speed
        // The position of this statements is important. If they are not in this position, the
        // racing cars would not move up or down when the cars are speeding up for the first time.
        if (m_player->getSpeed()<=getSpeed())
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
        updateSpeedRandom();

        updateMoveSpeed();
        doHorizontalMovement();
    }

    /**
     * Determine if the car can be destroyed.
     * @return False, a race car cannot be destroyed.
     */
    bool RacingCar::canBeDestroyed() const
    {
        return false;
    }

    /**
     * Constructor of Racing car.
     * This constructor also initializes the corners and position, the cooldown timer, the move speed, the repair
     * time, the last move the car made, the cooldown time and the ID. The static value of CAR_COUNT is
     * increased by one.
     * @param player Shared pointer to the player.
     * @param world Shared pointer to the world.
     */
    RacingCar::RacingCar(const shared_ptr<Player>& player, const shared_ptr<World>& world)
            :m_player(player), m_world(world), m_lastMoveHorizontal(move::NONE), m_cooldownTime(500), m_id(CAR_COUNT),
             m_gameStarted(false)
    {
        setType(EntityType::RACE_CAR);

        double width = 0.24;
        double height = 0.40;
        double maxPlayer = player->getMaxSpeed(true);
        m_range.first = maxPlayer*3/4;
        m_range.second = maxPlayer*2.5;
        initializeCorners(width, height);
        initializePosition();

        m_moveCooldown.setTimer(m_cooldownTime);
        m_moveCooldown.startTimer();

        auto rand = Random::getInstance();
        m_moveSpeed = rand->randDouble(3.5, 4);
        setMoveSpeed(m_moveSpeed);

        setRepairTime(1000);

        CAR_COUNT++;
    }

    RacingCar::~RacingCar()
    {
        CAR_COUNT--;
    }

    void RacingCar::initializePosition()
    {
        if (m_id==0)
            setPos(0.55, 1);
        else if (m_id==1) {
            setPos(0.85, 0.5);
        }
        else if (m_id==2) {
            setPos(0.55, 0);
        }
        else if (m_id==3) {
            setPos(0.85, -0.5);
        }
        else if (m_id==4) {
            setPos(0.55, -1.0);
        }
        else
            throw runtime_error("Too much racing cars created... (Created "+to_string(CAR_COUNT+1)
                    +" but there are only 5 allowed)");
    }


    /**
     * Updates the movement speed of the Racing car.
     */
    void RacingCar::updateMoveSpeed()
    {

    }

    /**
     * Does the horizontal movement.
     * @see update()
     */
    void RacingCar::doHorizontalMovement()
    {
        auto rand = Random::getInstance();

        double worldCenterX = (m_world->getLeftBoundary()+m_world->getRightBoundary())/2;

        // If there is a car up front, do a smart move
        if (carInPath() && getPos().x<worldCenterX) {
            moveRight(m_world->getRightBoundary());
//            return;
        }
        if (carInPath() && getPos().x>=worldCenterX) {
            moveLeft(m_world->getLeftBoundary());
//            return;
        }

        if (rand->randInt(0, 100)<70) // 70% chance car does not turn
            return;

        bool lastLeft = m_lastMoveHorizontal==move::LEFT;
        bool lastRight = m_lastMoveHorizontal==move::RIGHT;

        // move left or right randomly if possible
        if (m_lastMoveHorizontal==move::NONE) {
            if (rand->randInt(0, 100)<50)   // 50% chance
                moveLeft(m_world->getLeftBoundary());
            if (rand->randInt(0, 100)<50)   // 50% chance
                moveRight(m_world->getRightBoundary());
        }
        if (lastLeft) {
            if (rand->randInt(0, 100)<75)   // 75% chance
                moveLeft(m_world->getLeftBoundary());
        }
        else if (lastRight) {
            if (rand->randInt(0, 100)<75)     // 75% chance
                moveRight(m_world->getRightBoundary());
        }
    }

    /**
     * Updates the speed of the race car.
     * @see update()
     */
    void RacingCar::updateSpeedRandom()
    {
        auto rand = Random::getInstance();
        if (rand->randInt(0, 100)<60)   // 60% chance
            accelerate();
        if (rand->randInt(0, 100)<75) // 75% chance
            slowDown();

    }

    /**
     * Checks if a car is in the path the car is following.
     * @return True if a car is in the path
     */
    bool RacingCar::carInPath() const
    {
        for (const auto& entity : m_world->getEntities()) {
            if (entity.get()==this)
                continue;

            // entity is below this one
            if (entity->getUpperLeftCorner().y<getBottomRightCorner().y)
                continue;

            if (entity->getBottomRightCorner().y-getUpperLeftCorner().y<getHeight()) {
                const Position& left = getUpperLeftCorner();
                const Position& right = getBottomRightCorner();
                double min = entity->getUpperLeftCorner().x;
                double max = entity->getBottomRightCorner().x;

                if (left.x>=min && left.x<=max)
                    return true;
                if (right.x>=min && right.x<=max)
                    return true;
            }
        }
        return false;
    }


} // namespace RoadFighter
