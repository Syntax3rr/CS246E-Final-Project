#ifndef AGE_ENTITIES_COLLISION_DERIVATIVES_BOUNCE_H
#define AGE_ENTITIES_COLLISION_DERIVATIVES_BOUNCE_H
#include "../collision-base.h"
#include "../../entity.h"

namespace age {
    class Bounce : public CollisionBase {
    public:
        Bounce(Entity& entity) : CollisionBase(entity) {}
        Bounce(const Bounce& other) : CollisionBase(other) {}

        virtual bool onCollision(int vx, int vy, CollisionBase* other) {
            entity.vx = -entity.vx;
            entity.vy = -entity.vy;
            return true;
        }
    };
    };
}
