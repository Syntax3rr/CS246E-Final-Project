#ifndef AGE_EVENTS_EVENT_H
#define AGE_EVENTS_EVENT_H
#include "event-types.h"

namespace age {
    class Event {
        EventType type; // The trigger for the event
    public:
        virtual void onEvent() = 0;
        virtual Event* clone() const = 0;
    };
}

#endif
