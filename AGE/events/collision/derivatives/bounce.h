#ifndef AGE_EVENTS_COLLISION_BOUNCE_H
#define AGE_EVENTS_COLLISION_BOUNCE_H
#include "../event.h"
#include "../../engine/objects/entity.h"

namespace age {
    class Bounce : public Event {
        Entity* entity;
    public:
        Bounce() : entity(nullptr) {}
        Bounce(Entity& entity) : entity(&entity) {}
        void onEvent() {
            entity->bounce();
        }
    };
}
