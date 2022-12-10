#ifndef AGE_UPDATEEVENTS_STATE_CALLBACKCLOCK_H
#define AGE_UPDATEEVENTS_STATE_CALLBACKCLOCK_H
#include <functional>
#include "../update-event.h"

namespace age {
    class CallbackClock : public UpdateEvent {
        unsigned int ticksPerCycle;
        std::function<void()> callback;
        unsigned int ticks = 0;
    public:
        CallbackClock(unsigned int ticksPerCycle, std::function<void()> callback) : ticksPerCycle(ticksPerCycle), callback(callback) {}
        CallbackClock(const CallbackClock& other) : ticksPerCycle(other.ticksPerCycle), callback(other.callback) {}

        void onEvent() {
            if(++ticks >= ticksPerCycle) {
                ticks = 0;
                callback();
            }
        }
    };
}

#endif
