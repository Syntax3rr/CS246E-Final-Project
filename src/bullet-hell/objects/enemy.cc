#include "enemy.h"
#include "../update-type/fire-bullet.h"

namespace bulletHell {
    Enemy::Enemy(BulletHell& engine, Vec pos, char c, int health, initializer_list<EntityMovement*> movement, initializer_list<EntityMovement*> bulletTrajectory, int rateOfFire):
        Entity(pos.x, pos.y, 1, c, false, { new FireBullet(engine, 'o', Vec{-1, 0}, rateOfFire) }), health(health) {}

    Enemy::Enemy(BulletHell& engine, Vec pos, char c, int health, initializer_list<EntityMovement*> movement, int rateOfFire):
        Entity(pos.x, pos.y, 1, c, false, { new FireBullet(engine, 'o', Vec{-1, 0}, rateOfFire) }), health(health) {}

    void Enemy::damage(int damage) {
        if (health -= damage <= 0 || damage == -1) {
            setPos(Vec{ 300, 300 });
            stop();
        }
    }
}

