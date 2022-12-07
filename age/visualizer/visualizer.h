#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <string>
#include <vector>
#include <map>
#include "../engine-constants.h"
#include "../engine/engine.h"
#include "../engine/objects/sprite.h"

namespace age {
    class Engine;

    class Visualizer {
        Engine& engine;
        //std::map<size_t, char[C_HEIGHT][C_WIDTH]> canvas; //Full 3D canvas space, [z][y][x]
        //bool canvasDiff[C_HEIGHT][C_WIDTH]; //Keeps track of which parts of the canvas have changed
        char tlcanvas[C_HEIGHT][C_WIDTH]; //Top layer canvas, [y][x], a collapsed version of the canvas
        std::string textLines[3]; //Text lines, [line]
        
        void loadCanvas(); //Load canvas data from engine
        void collapseCanvas(); //Collapse canvas data into tlcanvas
    protected:
        char getCanvas(int x, int y) const {
            return tlcanvas[y][x];
        };
        std::string getTextLine(int i) const {
            return textLines[i];
        };
        virtual void updateScreen() = 0;
    public:
        Visualizer(Engine& engine) : engine(engine) {}
        void update() {
            loadCanvas();
            updateScreen();
        }
    };
}

#endif
