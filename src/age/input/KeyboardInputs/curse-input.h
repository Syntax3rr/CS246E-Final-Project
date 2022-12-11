#ifndef AGE_INPUT_KEYBOARDINPUTS_CURSEINPUT_H
#define AGE_INPUT_KEYBOARDINPUTS_CURSEINPUT_H
#include "../input.h"
#include <ncurses.h>

namespace age {
    class CurseInput: public Input {
        void updateKeyStates() override;
    public:
        CurseInput();
    };
}

#endif
