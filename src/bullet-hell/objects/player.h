#ifndef BULLETHELL_OBJECTS_PLAYER_H
#define BULLETHELL_OBJECTS_PLAYER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "../game-constants.h"
#include "../../age/engine-constants.h"
#include "../../age/helpers/math/vec.h"
#include "../../age/engine/objects/entity.h"
#include "../../age/input/input.h"

namespace bulletHell {
    using namespace age;
    using std::vector;
    using std::unique_ptr;

    class BulletHell;

    class Player: public age::Entity {
        age::Input& input;
        int lives = MAX_LIVES;
        int invincibilityTimer = 0;

    public:
        Player(age::Sprite sprite, BulletHell& engine);

        bool onUpdate();

        void damage();

        int getLives() const { return lives; }

        ~Player() {}
    };
}

#endif
