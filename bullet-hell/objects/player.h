#ifndef BULLETHELL_OBJECTS_PLAYER_H
#define BULLETHELL_OBJECTS_PLAYER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "../game-constants.h"
#include "../../engine-constants.h"
#include "../../helpers/math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "../../age/engine/objects/movement/movementTypes/move-by-user.h"
#include "../../age/engine/objects/entity.h"

using namespace age;
using std::vector;
using std::unique_ptr;
namespace bulletHell {
    age::Input;

    class Player: public age::Entity {
        age::Input& input;
        int lives = MAX_LIVES;

        vector<unique_ptr<UpdateType>> updates{};
        vector<unique_ptr<EntityCollision>> collisions{};
        vector<unique_ptr<EntityMovement>> movements{
           std::make_unique<MoveByUser>(MoveByUser(input))
        };
    public:
        Player(int x, int y, int z, age::Sprite sprite, age::Input& input): age::Entity(x, y, z, sprite, true, updates, collisions, movements), input(input) {}
    };
}

#endif
