#ifndef ROADFIGHTER_BULLET_H
#define ROADFIGHTER_BULLET_H

#include "Entity.h"

namespace RoadFighter {

    /**
     * Class which represents a bullet shot by the @see Player.
     */
    class Bullet : public Entity {
    private:
        double m_shootSpeed;
        Position m_pos;
        bool m_hit;
    public:
        /**
         * Constructor for Bullet.
         * @param shootSpeed shooting speed of the bullet.
         */
        Bullet(double shootSpeed, const Position& playerPos, double playerHeight);

        void update() override;

        /**
         * Assignment operator for Bullet.
         * @param other The other bullet.
         * @return Reference to bullet which is equal to other.
         */
        Bullet& operator=(const Bullet& other);

        /**
         * Default destructor for Bullet.
         */
        ~Bullet() override;

        /**
         * Getter for the shooting speed of the Bullet.
         * @return Shooting speed of the Bullet.
         */
        double getShootSpeed() const;

        /**
         * Setter for the shooting speed of the Bullet.
         * @param speed New shooting speed for the Bullet.
         */
        void setShootSpeed(double speed);

        void hit();

        bool canBeDestroyed() const override;
    };

} // namespace RoadFighter

#endif //ROADFIGHTER_BULLET_H
