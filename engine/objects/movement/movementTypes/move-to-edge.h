#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVETOEDGE_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVETOEDGE_H
#include "entity-movement.h"
#include "../../helpers/math/vec.h"

namespace age {
    struct MoveToEdge : public EntityMovement {
        enum struct Edge {
            LEFT,
            RIGHT,
            TOP,
            BOTTOM
        };

        Edge target;

        Vec& move(Vec& vel) override {
            switch (target) {
                case Edge::LEFT:
                    vel.x--;
                    break;
                case Edge::RIGHT:
                    vel.x++;
                    break;
                case Edge::TOP:
                    vel.y--;
                    break;
                case Edge::BOTTOM:
                    vel.y++;
                    break;
            }
            return vel;
        }
    };
}

#endif
