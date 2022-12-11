#include "curse-visualizer.h"
#include "../../engine-constants.h"
#include <ncurses.h>

namespace age {
    CurseVisualizer::CurseVisualizer(Engine& engine) : Visualizer(engine) {
        setlocale(LC_ALL, "");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

        //Draw Border
        for (int i = 0; i < S_HEIGHT; i++) {
            for (int j = 0; j < S_WIDTH; j++) {
                bool xCond = (j == 0 || j == S_WIDTH - 1) && i <= C_HEIGHT + 1;
                bool yCond = (i == 0 || i == C_HEIGHT + 1);

                if (xCond && yCond) { //Draw Border
                    mvaddch(i, j, '+');
                } else if (xCond) {
                    mvaddch(i, j, '|');
                } else if (yCond) {
                    mvaddch(i, j, '-');
                }
            }
        }
    }

    void CurseVisualizer::updateScreen() {
        //Draw Canvas
        for (int i = 0; i < C_HEIGHT; i++) {
            for (int j = 0; j < C_WIDTH; j++) {
                mvaddch(i + 1, j + 1, getCanvas(j, i));
            }
        }

        //Draw Text
        for (int i = 0; i < 3; i++) {
            mvaddstr(C_HEIGHT + 2 + i, 1, getTextLine(i).c_str());
        }

        refresh();
    }
}
