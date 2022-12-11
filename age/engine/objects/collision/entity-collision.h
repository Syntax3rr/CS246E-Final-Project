#ifndef AGE_ENGINE_OBJECTS_COLLISION_ENTITYCOLLISION_H
#define AGE_ENGINE_OBJECTS_COLLISION_ENTITYCOLLISION_H
#include <memory>

namespace age {
    class Entity;

    struct EntityCollision {
        virtual void onCollision(Entity& entity, Entity& other) = 0;

        virtual std::unique_ptr<EntityCollision> clone() const = 0;
    };
}

#endif
