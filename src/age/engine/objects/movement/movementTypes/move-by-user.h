#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_MOVEMENTTYPES_MOVEBYUSER_H
#include "../entity-movement.h"
#include "../../../../input/input.h"
#include <ncurses.h>

namespace age {
    struct MoveByUser: public EntityMovement {
        Input& input;

        int forwardKey;
        int backwardKey;
        int leftKey;
        int rightKey;

        MoveByUser(Input& input, int forwardKey = 'w', int backwardKey = 's' , int leftKey = 'a', int rightKey = 'd'): input(input), forwardKey(forwardKey), backwardKey(backwardKey), leftKey(leftKey), rightKey(rightKey) {}
        MoveByUser(const MoveByUser& other): input(other.input), forwardKey(other.forwardKey), backwardKey(other.backwardKey), leftKey(other.leftKey), rightKey(other.rightKey) {}

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
