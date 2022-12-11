#include "raw-console-visualizer.h"
#include "../../engine-constants.h"

namespace age {
    void RawConsoleVisualizer::drawScreen() {
        for (int i = 0; i < S_HEIGHT; i++) {
            for (int j = 0; j < S_WIDTH; j++) {
                bool xCond = (j == 0 || j == S_WIDTH - 1) && i <= C_HEIGHT + 1;
                bool yCond = (i == 0 || i == C_HEIGHT + 1);

                int x = j - 1;
                int y = i - 1;
                bool canvasCond = (x >= 0 && x < C_WIDTH && y >= 0 && y < C_HEIGHT);

                if (xCond && yCond) { //Draw Border
                    out << "+";
                } else if (xCond) {
                    out << "|";
                } else if (yCond) {
                    out << "-";
                } else if (canvasCond) { //Draw Canvas
                    out << getCanvas(x, y);
                } else { //Draw Text
                    out << getTextLine(i - S_HEIGHT + 3);
                    break;
                }
            }
            out << i << '\r' << std::endl;
        }
    }
}
