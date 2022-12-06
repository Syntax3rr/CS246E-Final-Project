#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#include "entity-movement.h"
#include "../../../input/input.h"

namespace age {
    struct MoveByUser : public EntityMovement {
        Input* input;

        Vec& move(Vec& vel) override {
            if (input->getKeyState('w')) {
                vel.y--;
            } 
            if (input->getKeyState('s')) {
                vel.y++;
            }
            if (input->getKeyState('a')) {
                vel.x--;
            } 
            if (input->getKeyState('d')) {
                vel.x++;
            }
            return vel;
        }
    };
}

#endif
