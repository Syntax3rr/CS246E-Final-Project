#ifndef AGE_UPDATEEVENTS_STATE_CALLBACKONINPUT_H
#define AGE_UPDATEEVENTS_STATE_CALLBACKONINPUT_H
#include <functional>
#include "../update-event.h"
#include "../../input/input.h"

namespace age {
    class CallbackOnInput : public UpdateEvent {
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
