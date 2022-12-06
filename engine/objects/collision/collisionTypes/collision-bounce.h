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
                //Check what side of the other entity the entity is on, and bounce off of that side. //include width and height
                if (entity.getPos().x + entity.getWidth() < other.getPos().x || entity.getPos().x > other.getPos().x + other.getWidth()) {
                    if (entity.getPos().y + entity.getHeight() < other.getPos().y || entity.getPos().y > other.getPos().y + other.getHeight()) {
                        entity.setVel(entity.getVel() * -1);
                    } else {
                        entity.setVel(Vec{ entity.getVel().x * -1, entity.getVel().y });
                    }
                } else {
                    if (entity.getPos().y + entity.getHeight() < other.getPos().y || entity.getPos().y > other.getPos().y + other.getHeight()) {
                        entity.setVel(Vec{ entity.getVel().x, entity.getVel().y * -1 });
                    } else {
                        entity.setVel(entity.getVel() * -1);
                    }
                }
            } else if (entity.getVel().x != 0) {
                entity.setVel(Vec{ -entity.getVel().x, entity.getVel().y });
            } else if (entity.getVel().y != 0) {
                entity.setVel(Vec{ entity.getVel().x, -entity.getVel().y });
            }
        }
    };
}

#endif
