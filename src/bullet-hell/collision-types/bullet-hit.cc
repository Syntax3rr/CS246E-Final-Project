#include "bullet-hit.h"

namespace bulletHell {      
    BulletHit::BulletHit(bool friendly): friendly(friendly) {}

    void BulletHit::onCollision(Entity& entity, Entity& other) {
        dynamic_cast<Bullet&>(entity).damage();
        
        if (!friendly && other.isPlayerControlled()) {
            dynamic_cast<Player&>(other).damage();
        } else if (friendly) {
            dynamic_cast<Enemy&>(other).damage();
        }
    }
    
    std::unique_ptr<EntityCollision> BulletHit::clone() const {
        return std::make_unique<BulletHit>(*this);
    }
}
