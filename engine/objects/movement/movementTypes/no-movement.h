#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_NOMOVEMENT_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_NOMOVEMENT_H
#include "entity-movement.h"

namespace age {
    struct NoMovement : public EntityMovement {
        Vec& move(Vec& vel) override {
            EntityMovement::move(vel);
        }
    };
}

#endif
