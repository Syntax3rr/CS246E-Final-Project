#ifndef AGE_INPUT_KEYBOARDINPUTS_RAWCONSOLEINPUT_H
#define AGE_INPUT_KEYBOARDINPUTS_RAWCONSOLEINPUT_H
#include <memory>
#include <iostream>
#include <sys/poll.h>
#include <termios.h>
#include "../input.h"

namespace age {
    class RawConsoleInput : public Input {
        struct termios prevSettings;
        struct pollfd inputPoll;
        void updateKeyStates() override;
    public:
        RawConsoleInput();
        ~RawConsoleInput();
    };
}

#endif
