#ifndef AGE_EVENTS_MOVEMENT_MOVEMENTBASE_H
#define AGE_EVENTS_MOVEMENT_MOVEMENTBASE_H
#include "../event.h"
#include "../../entities/entity.h"

namespace age {
    class MovementBase: public Event {
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
        MovementBase(const MovementBase& other): entity(nullptr), vx(other.vx), vy(other.vy) {}

        virtual const bool isPlayerControlled() const = 0; // Tag to indicate whether the movement is player controlled

        virtual MovementBase* clone() const = 0;

        virtual void initialize(Entity& entity) {
            if (this->entity != nullptr) {
                throw "MovementBase::initialize() called on an already initialized MovementBase";
            }
            this->entity = &entity;
        }
    };
}

#endif
