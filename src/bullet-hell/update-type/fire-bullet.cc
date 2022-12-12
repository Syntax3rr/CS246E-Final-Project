#include "fire-bullet.h"

namespace bulletHell {
    FireBullet::FireBullet(BulletHell& engine, char bulletChar, Vec velocity, int rateOfFire):
        engine(&engine), bulletChar(bulletChar), velocity(velocity), rateOfFire(rateOfFire), input(nullptr), fireKey(-1) {}
    FireBullet::FireBullet(BulletHell& engine, char bulletChar, Vec velocity, int rateOfFire, Input* input, int fireKey):
        engine(&engine), bulletChar(bulletChar), velocity(velocity), rateOfFire(rateOfFire), input(input), fireKey(fireKey) {}
    FireBullet::FireBullet(const FireBullet& other):
        engine(other.engine), bulletChar(other.bulletChar), velocity(other.velocity), rateOfFire(other.rateOfFire), input(other.input) {}

    void FireBullet::onUpdate(Entity& entity) {
        if (input == nullptr || input->getKeyState(fireKey)) {
            if ((++frame %= rateOfFire) == 0) {
                engine->addEntity(new Bullet(entity.getPos(), bulletChar, velocity, entity.isPlayerControlled()));
            }
        }
    }
}
