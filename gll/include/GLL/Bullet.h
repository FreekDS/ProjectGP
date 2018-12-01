#ifndef ROADFIGHTER_BULLET_H
#define ROADFIGHTER_BULLET_H

#include "Entity.h"

namespace RoadFighter {

    class Bullet : public Entity {
    private:
        double m_shootSpeed;
    public:
        explicit Bullet(double m_shootSpeed);
        Bullet();
        Bullet& operator=(const Bullet& other);
        ~Bullet() override;
        double getShootSpeed() const;
        void setShootSpeed(double speed);
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_BULLET_H
