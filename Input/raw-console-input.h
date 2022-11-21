#ifndef AGE_INPUT_RAWCONSOLEINPUT_H
#define AGE_INPUT_RAWCONSOLEINPUT_H
#include <iostream>
#include <future>
#include "input.h"

namespace age {
    class RawConsoleInput : public Input {
        istream& input;
        char getInput();
        void updateKeyStates() override;
    }
}

#endif
