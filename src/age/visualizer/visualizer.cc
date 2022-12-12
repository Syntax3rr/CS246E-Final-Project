#include "visualizer.h"
#include "../engine-constants.h"
#include "../engine/objects/entity.h"
#include "../engine/engine.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <ncurses.h>

namespace age {
    void Visualizer::loadCanvas() {
        std::vector<Entity*> entities = engine->getEntities(); // Note the entities are sorted by their z-index.
        move(S_HEIGHT, 0);
        for (int i = 0; i < C_HEIGHT; i++) {
            for (int j = 0; j < C_WIDTH; j++) {
                auto k = std::find_if(entities.begin(), entities.end(), [i, j](Entity* e) {
                    char c = e->getAt(j, i);
                    return c > 32 && c < 127;
                    });

                tlcanvas[i][j] = k == entities.end() ? ' ' : (*k)->getAt(j, i);
            }
        }
        refresh();
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
            struct timespec ts = {0, (long) (sleepTime.count() * 1000000)};
            if (sleepTime.count() > 0) {
                nanosleep(&ts, NULL);
            }
        }
    }
}
