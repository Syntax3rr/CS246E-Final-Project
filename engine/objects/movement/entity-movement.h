#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#include "../../helpers/math/vec.h"

namespace age {
    struct EntityMovement {
        virtual Vec& move(Vec& vel) = 0;
    };
}

#endif
