#include "visualizer.h"

namespace age {
    void Visualizer::loadCanvas() {
        std::vector<Sprite> sprites = engine.getSprites();
        //TODO
    }

    void Visualizer::collapseCanvas() {
        for (int i = 0; i < C_HEIGHT; i++) {
            for (int j = 0; j < C_WIDTH; j++) {
                if (canvasDiff[i][j] == false) continue;
                tlcanvas[i][j] = ' ';
                for (auto k : canvas) {
                    if (k.second[i][j] != ' ') {
                        tlcanvas[i][j] = k.second[i][j];
                        break;
                    }
                }
            }
        }
    }
}
