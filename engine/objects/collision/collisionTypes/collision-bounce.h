#ifndef AGE_ENGINE_OBJECTS_COLLISION_COLLISIONTYPES_COLLISIONBOUNCE_H
#define AGE_ENGINE_OBJECTS_COLLISION_COLLISIONTYPES_COLLISIONBOUNCE_H
#include "../../entity.h"
#include "../entity-collision.h"
#include "../../../../helpers/math/vec.h"

namespace age {
    struct CollisionBounce : public EntityCollision {
        void onCollision(Entity& entity, Entity& other) override { //Note, this only does a bounce assuming the normal vector is axis-aligned.
            if (entity.getVel().x == 0 && entity.getVel().y == 0) return;
            if (entity.getVel().x != 0 && entity.getVel().y != 0) {
                entity.setVel(Vec{ -entity.getVel().x, 0 });
                return;
            }
            if (entity.getVel().x != 0) {
                entity.setVel(Vec{ -entity.getVel().x, entity.getVel().y });
            } else if (entity.getVel().y > 0) {
                entity.setVel(Vec{ entity.getVel().x, -entity.getVel().y });
            }
        }
    };
}

#endif
