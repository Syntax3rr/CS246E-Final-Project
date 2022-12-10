#ifndef AGE_EVENTS_MOVEMENT_DERIVATIVES_STRAIGHTLINE_H
#define AGE_EVENTS_MOVEMENT_DERIVATIVES_STRAIGHTLINE_H
#include "../movement-base.h"
#include "../../../entities/entity.h"

namespace age {
    class StraightLine : public MovementBase {
    public:
        StraightLine(Entity& entity, int vx, int vy) : MovementBase(entity, vx, vy) {}

        virtual const bool isPlayerControlled() const {return false;}

        MovementBase* clone() const {return new StraightLine(*this);}
    };
}

#endif
