#ifndef BULLETHELL_OBJECTS_BULLET_H
#define BULLETHELL_OBJECTS_BULLET_H
#include "../../age/engine/objects/entity.h"
#include "../../age/helpers/math/vec.h"
#include "../../age/engine/objects/movement/entity-movement.h"
#include <initializer_list>

namespace bulletHell {
    using namespace age;
    using std::initializer_list;
    class Bullet: public Entity {
    public:
        Bullet(Vec pos, char c, Vec velocity, bool friendly = false);
        Bullet(Vec pos, char c, initializer_list<EntityMovement*> movement, bool friendly = false);

        void damage();
    };
}

#endif
