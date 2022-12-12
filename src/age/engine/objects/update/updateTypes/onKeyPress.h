#ifndef AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_ONKEYPRESS_H
#define AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_ONKEYPRESS_H
#include "../update-type.h"
#include "../../../../input/input.h"
#include "../../entity.h"
#include <memory>

namespace age {
    class OnKeyPress : public UpdateType {
        Input* input;
        int key;
    public:
        OnKeyPress(Input& input, int key) : input(&input), key(key) {}
        OnKeyPress(const OnKeyPress& other) : input(other.input), key(other.key) {}

        std::unique_ptr<UpdateType> clone() const override { return std::make_unique<OnKeyPress>(*this); }

        void onUpdate(Entity& entity) {
            if (input->getKeyState(key)) {
                entity.advanceState();
            }
        };

        std::unique_ptr<UpdateType> clone() const override { return std::make_unique<OnKeyPress>(*this); }
    };
}

#endif
