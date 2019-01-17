#include <WorldTests.h>
#include <EntityTests.h>
#include <GLL/PassingCar.h>

using namespace RoadFighter;

TEST_F(WorldTests, Constructor)
{
    WorldTest world;
    EXPECT_EQ(world.getUpperLeftCorner(), Position(-4, 3));
    EXPECT_EQ(world.getBottomRightCorner(), Position(4, -3));
    EXPECT_EQ(world.getType(), EntityType::WORLD);
    EXPECT_EQ(world.getPos(), Position());
    EXPECT_EQ(world.getPos(), Position(0,0));
    EXPECT_EQ(world.getLeftBoundary(), -0.7);
    EXPECT_EQ(world.getRightBoundary(), 1.3);
    EXPECT_EQ(world.getPlayer(), nullptr);
    EXPECT_TRUE(world.getEntities().empty());
    EXPECT_EQ(world.getFactory(), nullptr);
    EXPECT_TRUE(world.getColliders().empty());
    EXPECT_EQ(world.getHeight(), 6);
    EXPECT_EQ(world.getWidth(), 8);
}

TEST_F(WorldTests, AssignmentConstructor)
{
    WorldTest world;
    Position pos(12,21);
    world.setPos(pos);
    WorldTest world2 = world;
    EXPECT_EQ(world2.getPos(), world.getPos());
}

TEST_F(WorldTests, addEntity)
{
    WorldTest world;
    EXPECT_TRUE(world.getEntities().empty());
    shared_ptr<RoadFighter::Entity> entity = make_shared<EntityTest>();
    shared_ptr<RoadFighter::Entity> entity2 = make_shared<EntityTest>();
    world.add(entity);
    EXPECT_EQ(world.getEntities().size(), 1);
    world.add(entity2);
    EXPECT_EQ(world.getEntities().size(), 2);
}

TEST_F(WorldTests, removeEntity)
{
    WorldTest world;
    EXPECT_TRUE(world.getEntities().empty());
    shared_ptr<RoadFighter::Entity> entity = make_shared<EntityTest>();
    shared_ptr<RoadFighter::Entity> entity2 = make_shared<EntityTest>();
    world.add(entity);
    world.add(entity2);
    EXPECT_EQ(world.getEntities().size(), 2);
    world.remove(entity);
    EXPECT_EQ(world.getEntities().size(), 1);
    world.remove(entity);
    EXPECT_EQ(world.getEntities().size(), 1);
    world.remove(entity2);
    EXPECT_TRUE(world.getEntities().empty());
}

TEST_F(WorldTests, empty)
{
    WorldTest world;
    EXPECT_TRUE(world.empty());
    shared_ptr<RoadFighter::Entity> entity = make_shared<EntityTest>();
    world.add(entity);
    EXPECT_FALSE(world.empty());
}

TEST_F(WorldTests, checkCollision)
{
    WorldTest world;
    shared_ptr<RoadFighter::Entity> entity = make_shared<EntityTest>();
    shared_ptr<RoadFighter::Entity> entity2 = make_shared<EntityTest>();
    EXPECT_FALSE(world.checkCollision(entity, entity2));
    BoxCollider b1{Position(), Position(1,1)};
    BoxCollider b2{Position(), Position(1,1)};
    entity->addCollider(b1);
    entity2->addCollider(b2);
    EXPECT_TRUE(world.checkCollision(entity, entity2));
    EXPECT_TRUE(world.checkCollision(entity2, entity));
    b1.updateCollider(200,200);
    entity->removeCollider(0);
    entity->addCollider(b1);
    EXPECT_FALSE(world.checkCollision(entity, entity2));
    EXPECT_FALSE(world.checkCollision(entity2, entity));
}

TEST_F(WorldTests, canBeDestroyed)
{
    WorldTest world;
    EXPECT_FALSE(world.canBeDestroyed());
}

TEST_F(WorldTests, removeRemovableEntities)
{
    shared_ptr<World> world = make_shared<WorldTest>();
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<Entity> e1 = make_shared<PassingCarTest>(player, world);
    shared_ptr<Entity> e2 = make_shared<PassingCarTest>(player, world);
    shared_ptr<Entity> e3 = make_shared<PassingCarTest>(player, world);
    shared_ptr<Entity> e4 = make_shared<PassingCarTest>(player, world);
    shared_ptr<Entity> e5 = make_shared<PassingCarTest>(player, world);
    world->add(player);
    world->add(e1);
    world->add(e2);
    world->add(e3);
    world->add(e4);
    world->add(e5);
    ASSERT_EQ(world->getEntities().size(), 6);
    world->removeRemovableEntities();
    EXPECT_EQ(world->getEntities().size(), 6);
    e1->setPos(0, -20000);
    ASSERT_TRUE(e1->canBeDestroyed());
    world->removeRemovableEntities();
    EXPECT_EQ(world->getEntities().size(), 5);
    e3->setPos(0, -20000);
    e5->setPos(0, -20000);
    ASSERT_TRUE(e3->canBeDestroyed());
    ASSERT_TRUE(e5->canBeDestroyed());
    world->removeRemovableEntities();
    EXPECT_EQ(world->getEntities().size(), 3);
}

TEST_F(WorldTests, getPlayer)
{
    shared_ptr<World> world = make_shared<WorldTest>();
    shared_ptr<Player> player = make_shared<PlayerTest>();
    shared_ptr<PassingCar> e1 = make_shared<PassingCarTest>(player, world);
    shared_ptr<PassingCar> e2 = make_shared<PassingCarTest>(player, world);
    shared_ptr<PassingCar> e3 = make_shared<PassingCarTest>(player, world);
    shared_ptr<PassingCar> e4 = make_shared<PassingCarTest>(player, world);
    shared_ptr<PassingCar> e5 = make_shared<PassingCarTest>(player, world);
    world->add(player);
    world->add(e1);
    world->add(e2);
    world->add(e3);
    world->add(e4);
    world->add(e5);
    EXPECT_EQ(player.get(), world->getPlayer().get());
}


