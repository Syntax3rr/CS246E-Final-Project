#ifndef AGE_VISUALIZER_VISUALIZERS_RAWCONSOLEVISUALIZER_H
#define AGE_VISUALIZER_RAWCONSOLEVISUALIZER_H
#include <iostream>
#include "../visualizer.h"

namespace age {
    class Engine;

    class RawConsoleVisualizer : public Visualizer {
        std::ostream& out;

    public:
        RawConsoleVisualizer(Engine engine, std::ostream& out = std::cout) : Visualizer(engine), out(out) {}
        void clearScreen() { system("clear"); }
        void drawScreen();
        void updateScreen() override {
            clearScreen();
            drawScreen();
        }
    };

}


#endif
