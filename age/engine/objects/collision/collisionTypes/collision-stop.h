#ifndef AGE_ENGINE_OBJECTS_COLLISION_COLLISIONTYPES_COLLISIONSTOP_H
#define AGE_ENGINE_OBJECTS_COLLISION_COLLISIONTYPES_COLLISIONSTOP_H
#include "../../entity.h"
#include "../entity-collision.h"
#include "../../helpers/math/vec.h"

namespace age {
    struct CollisionStop : public EntityCollision {
        void onCollision(Entity& entity, Entity& other) override {
            entity.stop();
        }
    };
}

#endif
