#ifndef AGE_EVENTS_COLLISION_STOPMOTION_H
#define AGE_EVENTS_COLLISION_STOPMOTION_H
#include "../event.h"
#include "../../engine/objects/entity.h"

namespace age {
    class StopMotion : public Event {
        Entity* entity;
    public:
        StopMotion(Entity& entity) : entity(&entity) {}
        void onEvent() {
            entity->stop();
        }
    };
}

#endif
