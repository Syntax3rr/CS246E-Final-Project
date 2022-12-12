#include "player.h"
#include "../update-type/fire-bullet.h"
#include "../game/bullethell.h"
#include "../../age/engine/objects/movement/movementTypes/move-by-user.h"
#include "../../age/engine/objects/sprite.h"

namespace bulletHell {
    using namespace age;
    using std::vector;
    using std::unique_ptr;

    Player::Player(Sprite sprite, BulletHell& engine):
        age::Entity(RESPAWN_X, RESPAWN_Y, 1, sprite, true,
            {
                new FireBullet(engine, '>', Vec(2, -1), 10),
                new FireBullet(engine, '>', Vec(2, 0), 10),
                new FireBullet(engine, '>', Vec(2, -1), 10)
            },
            {},
            { new MoveByUser(*(engine.input), KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT) }), input(*(engine.input)) {}

    bool Player::onUpdate() {
        if (invincibilityTimer > 0) invincibilityTimer--;
        return true;
    }

    void Player::damage() {
        if (invincibilityTimer > 0) return;
        --lives;
        invincibilityTimer = INVINCIBILITY_FRAMES;
        pos.set(RESPAWN_X, RESPAWN_Y);
        stop();
    }
}
