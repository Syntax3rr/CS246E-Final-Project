#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEINLINE_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEINLINE_H
#include "entity-movement.h"
#include "../../helpers/math/vec.h"

namespace age {
    struct MoveInLine : public EntityMovement {
        Vec velocity; // The line to move in.

        Vec& move(Vec& vel) override {
            vel += velocity;
            return vel;
        }
    };
}

#endif
