#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEINLINE_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEINLINE_H
#include "../entity-movement.h"

namespace age {
    struct MoveInLine : public EntityMovement {
        Vec velocity; // The line to move in.

        MoveInLine(Vec velocity) : velocity(velocity) {}    
        MoveInLine(const MoveInLine& other) : velocity(other.velocity) {}

        Vec& move(Vec& vel) override {
            vel += velocity;
            return vel;
        }

        std::unique_ptr<EntityMovement> clone() const override { return std::make_unique<MoveInLine>(*this); }
    };
}

#endif
