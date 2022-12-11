#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#include "../entity-movement.h"
#include "../../../../input/input.h"

namespace age {
    struct MoveByUser: public EntityMovement {
        Input& input;

        char forwardKey = 'w';
        char backwardKey = 's';
        char leftKey = 'a';
        char rightKey = 'd';

        MoveByUser(Input& input): input(input) {}

        Vec& move(Vec& vel) override {
            if (input.getKeyState(forwardKey)) {
                vel.y--;
            }
            if (input.getKeyState(backwardKey)) {
                vel.y++;
            }
            if (input.getKeyState(leftKey)) {
                vel.x--;
            }
            if (input.getKeyState(rightKey)) {
                vel.x++;
            }
            return vel;
        }

        const bool isPlayerControlled() const override { return true; }

        std::unique_ptr<EntityMovement> clone() const override { return std::make_unique<MoveByUser>(*this); }
    };
}

#endif
