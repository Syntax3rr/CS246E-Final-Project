#ifndef AGE_EVENTS_MOVEMENT_DERIVATIVES_GRAVITATEEDGE_H
#define AGE_EVENTS_MOVEMENT_DERIVATIVES_GRAVITATEEDGE_H
#include "../movement-base.h"
#include "../../../entities/entity.h"

namespace age {
    enum Edge {
        LEFT, RIGHT, TOP, BOTTOM
    };

    class GravitateEdge: public MovementBase {
    public:
        GravitateEdge(Edge edge, int velocity, Entity& entity): 
        MovementBase(
            entity, 
            edge == Edge::LEFT ? -velocity : edge == Edge::RIGHT ? velocity : 0,
            edge == Edge::TOP ? -velocity : edge == Edge::BOTTOM ? velocity : 0
        ) {}
        GravitateEdge(const GravitateEdge& other): MovementBase(other) {}

        virtual const bool isPlayerControlled() const {return false;}

        MovementBase* clone() const {return GravitateEdge(*this);}

        MovementBase& 
    };
}

#endif
