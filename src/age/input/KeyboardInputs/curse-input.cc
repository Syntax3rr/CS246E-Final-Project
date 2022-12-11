#include "curse-input.h"
#include <ncurses.h>

namespace age {
    CurseInput::CurseInput() {}

    void CurseInput::updateKeyStates() {
        int ch;
        clearKeys();
        while (ch = getch() != ERR) {
            setKey(ch, true);
        }
    }             
}
