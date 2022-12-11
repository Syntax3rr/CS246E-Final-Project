#include "visualizer.h"
#include "../engine-constants.h"
#include "../engine/objects/entity.h"
#include "../engine/engine.h"
#include <iostream>
#include <chrono>
#include <unistd.h>

namespace age {
    void Visualizer::loadCanvas() {
        std::vector<Entity*> entities = engine->getEntities();

        //Clear the canvas
        for (int i = 0; i < C_HEIGHT; i++) {
            for (int j = 0; j < C_WIDTH; j++) {
                tlcanvas[i][j] = ' ';
            }
        }
        //Load the canvas
        for (auto i : entities) {
            Sprite sprite = i->getSprite();
            Vec pos = i->getPos();
            std::vector<std::vector<char>> spriteData = sprite.getData();

            for (int j = 0; j < sprite.getHeight(); j++) {
                for (int k = 0; k < sprite.getWidth(); k++) {
                    tlcanvas[pos.y + j][pos.x + k] = spriteData[j][k] == '\0' ? ' ' : spriteData[j][k];
                }
            }
        }
    }

    std::string Visualizer::getTextLine(int i) const {
        if (i < 0 || i >= 3) return "";
        return engine->getTextLines()[i];
    }

    void Visualizer::start() {
        if (started) return;
        started = true;

        while (true) {
            auto start = std::chrono::high_resolution_clock::now();
            engine->update();
            update();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::chrono::duration<double, std::milli> sleepTime = std::chrono::duration<double, std::milli>(1000.0 / FRAME_RATE) - elapsed;
            engine->setTextLine(0, "Frame Time: " + std::to_string(elapsed.count()) + "ms");
            if (sleepTime.count() > 0) {
                usleep(sleepTime.count());
            }

        }
    }
}
