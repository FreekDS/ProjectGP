#ifndef ROADFIGHTER_FINISHLINE_H
#define ROADFIGHTER_FINISHLINE_H

#include "Entity.h"
#include "World.h"

namespace RoadFighter {

    class FinishLine : public Entity {
    public:

        /**
         * Constructor of the FinishLine.
         * Initializes the width of the finish line based on the world borders.
         * Initializes the corners of the finish line.
         * Initializes the position of the finish line.
         * @param world Shared pointer to the world.
         */
        explicit FinishLine(const shared_ptr<World>& world);

        /**
         * Check whether the finish line can be destroyed or not.
         * @return False
         */
        bool canBeDestroyed() const override;

        /**
         * Update function. Does nothing.
         */
        void update() override{}

        /**
         * Draw function. Does nothing.
         */
        void draw() const override {}

        /**
         * Updates the sprite location. Does nothing as the finish line does not have a sprite.
         */
        void updateSpriteLocation() override {}
    };

}

#endif //ROADFIGHTER_FINISHLINE_H
