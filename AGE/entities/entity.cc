#include "entity.h"

namespace age {
    Entity::update() {
        for (auto& event : eventHandlers[EventType::UPDATE]) {
            event->onEvent();
        }
    }
}
