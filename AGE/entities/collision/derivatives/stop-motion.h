#ifndef AGE_COLLISION_DERIVATIVES_STOPMOTION_H
#define AGE_COLLISION_DERIVATIVES_STOPMOTION_H
#include "../collision-base.h"
#include "../../entity.h"

namespace age {
    class StopMotion : public CollisionBase {
    public:
        StopMotion(Entity* entity) : CollisionBase(entity) {}
        StopMotion(const StopMotion& other) : CollisionBase(other) {}

        bool onCollision(int vx, int vy, CollisionBase* other) {
            
        }
    };
}

#endif
