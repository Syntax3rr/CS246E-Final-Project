#ifndef AGE_ENGINE_OBJECTS_COLLISION_ENTITYCOLLISION_H
#define AGE_ENGINE_OBJECTS_COLLISION_ENTITYCOLLISION_H

namespace age {
    class Entity;

    struct EntityCollision {
        virtual void onCollision(Entity& entity, Entity& other) = 0;
    };
}

#endif
