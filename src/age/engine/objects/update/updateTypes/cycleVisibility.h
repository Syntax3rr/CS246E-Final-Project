#ifndef AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_CYCLEVISIBILITY_H
#define AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPES_CYCLEVISIBILITY_H
#include <vector>
#include "../update-type.h"
#include "../../entity.h"

namespace age {
    class CycleVisiblity : public UpdateType {
        size_t cycleRate;
        size_t cycleCount;

    public:
        CycleVisiblity(size_t rate) : cycleRate(rate), cycleCount(0) {}
        CycleVisiblity(const CycleVisiblity& other) : cycleRate(other.cycleRate), cycleCount(other.cycleCount) {}
        CycleVisiblity(CycleVisiblity&& other) : cycleRate(other.cycleRate), cycleCount(other.cycleCount) {}

        void onUpdate(Entity& entity) {
            if (++cycleCount >= cycleRate) {
                cycleCount = 0;
                if (entity.isVisible()) {
                    entity.hide();
                } else {
                    entity.show();
                }
            }
        };

        std::unique_ptr<UpdateType> clone() const override { return std::make_unique<CycleVisiblity>(*this); }
    };
}

#endif
