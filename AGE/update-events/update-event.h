#ifndef AGE_UPDATEEVENTS_EVENT_H
#define AGE_UPDATEEVENTS_EVENT_H
#include "event-types.h"

namespace age {
    class UpdateEvent {
    public:
        virtual void onEvent() = 0;
        virtual UpdateEvent* clone() const = 0;
    };
}

#endif
