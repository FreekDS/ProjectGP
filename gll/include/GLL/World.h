#ifndef ROADFIGHTER_WORLD_H
#define ROADFIGHTER_WORLD_H

#include "Entity.h"
#include "EntityFactory.h"
#include "Player.h"
#include "Clock.h"
#include <vector>
#include <memory>

using namespace std;

namespace RoadFighter {

    /**
     * This class represents the World of Road Fighter.
     * Based on Composite design pattern.
     * A world has:
     * - A list of child entities.
     * - An abstract factory.
     * - Two boundaries (left and right).
     * - A clock used as cooldown for the spawning of entities.
     *
     * The world is derived from Entity and std::enable_shared_from_this to create
     * a shared pointer of this class.
     */
    class World : public Entity, public std::enable_shared_from_this<World> {
    protected:
        vector<shared_ptr<Entity>> m_childEntities;
        shared_ptr<EntityFactory> m_factory;
        double m_boundary1;
        double m_boundary2;
        Clock m_spawnCooldown;
        bool m_neededDistanceCovered;
        bool m_finishSpriteLoaded;
        bool m_stopLoop;
    public:
        /**
         * Default constructor of World.
         */
        World();

        const vector<shared_ptr<Entity>>& getEntities();

        /**
         * Setter for the Entity factory of the world.
         * @param factory EntityFactory of the world.
         */
        void setFactory(const shared_ptr<EntityFactory>& factory);

        /**
         * Getter for the EntityFactory of the world.
         * @return Reference to the EntityFactory.
         */
        const shared_ptr<EntityFactory>& getFactory() const;

        /**
         * Default destructor of World.
         */
        ~World() override;

        /**
         * Assignment operator for World.
         * @param other World to assign this one to.
         * @return Reference to a World object.
         */
        World& operator=(const World& other);

        /**
         * Adds an Entity to the world.
         * Part of the Composite design pattern.
         * @param entity Entity to add.
         */
        void add(shared_ptr<Entity> entity);

        /**
         * Remove an Entity of the world.
         * Part of the Composite design pattern.
         * @param entity Entity which needs to be removed.
         */
        void remove(shared_ptr<Entity> entity);

        /**
         * Check whether the world is empty or not.
         * @return True if the world has no Entities in it.
         */
        bool empty();

        /**
         * Check for collision between two entities.
         * @param entity1 First Entity to check.
         * @param entity2 Second Entity to check.
         * @return True if entity1 and entity2 collide.
         */
        bool checkCollision(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2) const;

        /**
         * Determine whether the Entity can be destroyed or not.
         * @return False, the world cannot be destroyed during the game.
         */
        bool canBeDestroyed() const override;

        /**
         * Searches for the player in the child entities and returns it if found.
         * @return Shared pointer of an entity (= the player), if nothing found, nullptr.
         */
        shared_ptr<Entity> getPlayer() const;

        /**
         * Getter for boundary1 of world.
         * @return Boundary1.
         */
        double getLeftBoundary() const;

        /**
         * Getter for boundary2 of world.
         * @return Boundary2.
         */
        double getRightBoundary() const;

        /**
         * Returns a shared pointer of this World.
         * @return Shared pointer of this world.
         */
        virtual shared_ptr<World> getPtr();

        /**
         * Removes all entities that can be removed from the list.
         */
        void removeRemovableEntities();

        /**
         * Resets the spawn timer.
         */
        void resetSpawnTimer();

        /**
         * Checks all entities for collision.
         */
        void checkCollisionOfAll() const;

        /**
         * This pure virtual function is needed to read input.
         */
        virtual void readInput() = 0;

        /**
         * Updates the world and all its components.
         * This function first updates all the components.
         * After that it will read the input with @see readInput().
         */
        void update() override;

        /**
         * Sets the racing cars.
         */
        void setupRaceCars();

        //TODO
        bool neededDistanceCovered() const;

        bool finishSpriteLoaded() const;

        void spawnFinishline();
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_WORLD_H
