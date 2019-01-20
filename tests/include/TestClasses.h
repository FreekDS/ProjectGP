#ifndef ROADFIGHTER_TESTCLASSES_H
#define ROADFIGHTER_TESTCLASSES_H

/**
 * @file This file contains derived classes of all abstract classes of GLL.
 * All pure virtual methods are implemented as methods which do nothing.
 * The classes created in this file are intended to test the non abstract functionality of the base classes
 * of the Game Logic Library. Some classes also have a reset function which is used in the test fixtures.
 */

#include <GLL/World.h>
#include <GLL/Entity.h>
#include <GLL/PassingCar.h>
#include <GLL/Player.h>
#include <GLL/Bullet.h>
#include <GLL/Observer.h>
#include <GLL/FinishLine.h>
#include <GLL/RacingCar.h>
#include <GLL/Vehicle.h>

class WorldTest : public RoadFighter::World {
public:
    void draw() const override { }

    void updateSpriteLocation() override { }

    void readInput() override { }

    void resetWorld()
    {
        *this = WorldTest();
    }

    shared_ptr<World> getPtr() override
    {
        return World::getPtr();
    }
};

class EntityTest : public RoadFighter::Entity {
public:
    void draw() const override { }

    void update() override { }

    void updateSpriteLocation() override { }

    bool canBeDestroyed() const override
    {
        return false;
    }

    /**
     * Resests the Test Entity
     */
    void resetEntity()
    {
        EntityTest entity;
        *this = move(entity);
    }

    /**
     * Wrapper for protected setType function
     * @param type Type to set
     */
    void setTestType(const RoadFighter::EntityType& type)
    {
        this->setType(type);
    }
};

class PassingCarTest : public RoadFighter::PassingCar {
public:
    PassingCarTest(const shared_ptr<RoadFighter::Player>& player, const shared_ptr<RoadFighter::World>& world)
            :PassingCar(player, world) { }

    void draw() const override { }

    void updateSpriteLocation() override { }

    void rotateSprite(float angle) override { }
};

class PlayerTest : public RoadFighter::Player {
public:
    void draw() const override { }

    void updateSpriteLocation() override { }

    void setSpriteRotation(float angle) override { }

    void rotateSprite(float angle) override { }
};

class BulletTest : public RoadFighter::Bullet {
public:
    BulletTest(double shootSpeed, const RoadFighter::Position& playerPos, double playerHeight)
            :Bullet(shootSpeed, playerPos, playerHeight) { }

    void draw() const override { }

    void updateSpriteLocation() override { }
};

class SpeedObserverTest : public RoadFighter::SpeedObserver {
public:
    SpeedObserverTest(const shared_ptr<RoadFighter::Player>& subject, const string& str)
            :SpeedObserver(subject, str) { }

    void draw() const override { }
};

class DistanceObserverTest : public RoadFighter::DistanceObserver {
public:
    explicit DistanceObserverTest(const shared_ptr<RoadFighter::Player>& subject)
            :DistanceObserver(subject) { }
};

class ScoreObserverTest : public RoadFighter::ScoreObserver {
public:
    ScoreObserverTest(const shared_ptr<RoadFighter::Player>& subject, const string& msg)
            :ScoreObserver(subject, msg) { }

    void draw() const override {}

    void updateDrawable() override {}
};

class RacingCarTest : public RoadFighter::RacingCar {
public:
    RacingCarTest(const shared_ptr<RoadFighter::Player>& player, const shared_ptr<RoadFighter::World>& world)
            :RacingCar(player, world) { }

    void draw() const override { }

    void updateSpriteLocation() override { }

    void rotateSprite(float angle) override { }

    void setSpriteRotation(float angle) override { }
};

class VehicleTest : public RoadFighter::Vehicle {
public:
    void draw() const override { }

    void update() override { }

    bool canBeDestroyed() const override
    {
        return false;
    }

    void updateSpriteLocation() override { }

    void accelerate() override { }

    void slowDown() override { }

    void moveLeft(double world_boundary) override { }

    void moveRight(double world_boundary) override { }

    void moveUp() override { }

    void moveDown() override { }
};

#endif //ROADFIGHTER_TESTCLASSES_H
