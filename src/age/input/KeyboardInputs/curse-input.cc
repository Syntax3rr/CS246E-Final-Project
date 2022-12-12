#include "curse-input.h"
#include <ncurses.h>
#include <string>

namespace age {
    CurseInput::CurseInput() {
        setlocale(LC_ALL, "");
        cbreak();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    }

    void CurseInput::updateKeyStates() {
        clearKeys();
        int ch;
        while ((ch = getch()) != ERR) {
            setKey(ch, true);
        }
    }
}
