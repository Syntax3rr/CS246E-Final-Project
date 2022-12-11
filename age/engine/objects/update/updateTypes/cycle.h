#ifndef AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_CYCLE_H
#define AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_CYCLE_H
#include <vector>
#include "../update-type.h"
#include "../../entity.h"

namespace age {
    class Cycle : public UpdateType {
        size_t cycleRate = 1;
        size_t cycleCount = 0;
    public:
        Cycle(size_t rate) : cycleRate(rate) {}
        void onUpdate(Entity entity) {
            if (++cycleCount == cycleRate) {
                cycleCount = 0;
                entity.advanceState();
            }
        };

        std::unique_ptr<UpdateType> clone() const override { return std::make_unique<Cycle>(*this); }
    };
}

#endif
