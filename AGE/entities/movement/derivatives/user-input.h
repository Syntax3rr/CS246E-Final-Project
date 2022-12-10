#ifndef AGE_EVENTS_MOVEMENT_DERIVATIVES_USERINPUT_H
#define AGE_EVENTS_MOVEMENT_DERIVATIVES_USERINPUT_H
#include "../movement-base.h"
#include "../../../entities/entity.h"
#include "../../../input/input.h"

namespace age {
    class UserInput: public MovementBase {
        Input* input;

        void updateVelocity() {
            vx = input->isPressed('a') ? -1 : input->isPressed('d') ? 1 : 0;
            vy = input->isPressed('w') ? -1 : input->isPressed('s') ? 1 : 0;
        }
    public:
        UserInput(Entity& entity, Input* input): MovementBase(entity, 0, 0), input(input) {}
        UserInput(const UserInput& other, Entity& entity): MovementBase(other, entity), input(other.input) {}

        virtual const bool isPlayerControlled() const { return true; }

        UpdateEvent* clone(Entity& entity) const override { return new UserInput(*this, entity); }
    };
}

#endif
