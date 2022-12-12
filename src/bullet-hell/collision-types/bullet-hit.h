#ifndef BULLETHELL_COLLISIONTYPES_BULLETHIT_H
#define BULLETHELL_COLLISIONTYPES_BULLETHIT_H
#include "../../age/engine/objects/collision/entity-collision.h"
#include "../objects/player.h"
#include "../objects/enemy.h"
#include "../objects/bullet.h"
#include <memory>

namespace bulletHell {
    using namespace age;
    class BulletHit: public EntityCollision {
        bool friendly;
    public:
        BulletHit(bool friendly = false);
        
        void onCollision(Entity& entity, Entity& other) override;

        std::unique_ptr<EntityCollision> clone() const override;
    };
}

#endif
