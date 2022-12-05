#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#include "../../helpers/math/vec.h"
#include "../entity.h"
#include <vector>

namespace age {
    struct EntityMovement {
        virtual Vec& setVel(Vec& vel) {
            return vel;
        }
    };
}

#endif
