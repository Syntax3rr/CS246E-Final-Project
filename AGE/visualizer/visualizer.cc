#include "visualizer.h"
#include "../engine/objects/entity.h"

namespace age {
    void Visualizer::loadCanvas() {
        std::vector<Entity> entities = engine.getEntities();
        //Clear the canvas
        for (int i = 0; i < C_HEIGHT; i++) {
            for (int j = 0; j < C_WIDTH; j++) {
                tlcanvas[i][j] = ' ';
            }
        }
        //Load the canvas
        for (auto i : entities) {
            Sprite sprite = i.getSprite();
            Vec pos = i.getPos();
            for (int j = 0; j < sprite.getHeight(); j++) {
                for (int k = 0; k < sprite.getWidth(); k++) {
                    if (tlcanvas[pos.y + j][pos.x + k] == ' ') {
                        tlcanvas[pos.y + j][pos.x + k] = sprite.getAt(j, k);
                    }
                }
            }
        }

    }

    /*void Visualizer::collapseCanvas() {
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
    }*/
}
