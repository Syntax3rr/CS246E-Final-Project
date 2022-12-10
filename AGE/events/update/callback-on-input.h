#ifndef AGE_EVENTS_UPDATE_CALLBACKONINPUT_H
#define AGE_EVENTS_UPDATE_CALLBACKONINPUT_H
#include <functional>
#include "../event.h"
#include "../../input/input.h"

namespace age {
    class CallbackOnInput : public Event {
        Input* input;
        char key;
        std::function<void()> callback;
    public:
        void onEvent() {
            if(input->isPressed(key)) {
                callback();
            }
        }
    };
}

#endif
