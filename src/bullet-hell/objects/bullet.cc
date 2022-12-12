#include "bullet.h"
#include "../collision-types/bullet-hit.h"
#include "../../age/engine/objects/movement/movementTypes/move-in-line.h"

namespace bulletHell {
    using namespace age;
    Bullet::Bullet(Vec pos, char c, Vec velocity, bool friendly):
        Entity(pos.x, pos.y, 1, c, false, {},
            { new BulletHit(friendly) },
            { new MoveInLine(velocity) }) {}
    Bullet::Bullet(Vec pos, char c, std::initializer_list<EntityMovement*> movement, bool friendly):
        Entity(pos.x, pos.y, 1, c, false, {}, {}, movement) {}

    void Bullet::damage() {
        setPos(Vec{ 300, 300 });
        stop();
    }
}
