#ifndef AGE_ENTITIES_COLLISION_COLLISIONBASE_H
#define AGE_ENTITIES_COLLISION_COLLISIONBASE_H

namespace age {
    class Entity;

    class CollisionBase {
    protected:
        Entity* entity;
    public:
        CollisionBase(Entity* entity): entity(entity) {}
        CollisionBase(const CollisionBase& other): entity(nullptr) {}

        virtual ~CollisionBase() {}

        virtual void onCollision(int vx, int vy, CollisionBase* other) const = 0;

        virutal unique_ptr clone(Entity& entity) {

        }
    };
}

#endif
