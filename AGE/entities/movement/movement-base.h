#ifndef AGE_UPDATEEVENTS_MOVEMENT_MOVEMENTBASE_H
#define AGE_UPDATEEVENTS_MOVEMENT_MOVEMENTBASE_H
#include "../update-event.h"
#include "../../entities/entity.h"

namespace age {
    class MovementBase: public UpdateEvent {
    protected:
        Entity* entity;
        int vx, vy;
        virtual void updateVelocity();
    public:
        MovementBase(Entity& entity, int vx, int vy): entity(&entity), vx(vx), vy(vy) {}
        void onEvent() {
            updateVelocity();
            entity->move(vx, vy);
        }
        MovementBase(const MovementBase& other, Entity& entity): entity(&entity), vx(other.vx), vy(other.vy) {}

        virtual const bool isPlayerControlled() const = 0; // Tag to indicate whether the movement is player controlled

        virtual UpdateEvent* clone(Entity& entity) const = 0;
    };
}

#endif
