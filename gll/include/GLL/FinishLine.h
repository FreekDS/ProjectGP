#ifndef ROADFIGHTER_FINISHLINE_H
#define ROADFIGHTER_FINISHLINE_H

#include "Entity.h"
#include "World.h"

namespace RoadFighter {

    class FinishLine : public Entity {
    public:
        explicit FinishLine(const shared_ptr<World>& world);

        void update() override;

        bool canBeDestroyed() const override;
    };

}

#endif //ROADFIGHTER_FINISHLINE_H
