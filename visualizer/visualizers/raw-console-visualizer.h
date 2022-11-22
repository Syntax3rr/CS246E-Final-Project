#ifndef AGE_VISUALIZER_VISUALIZERS_RAWCONSOLEVISUALIZER_H
#define AGE_VISUALIZER_RAWCONSOLEVISUALIZER_H
#include <iostream>
#include "../visualizer.h"

namespace age {
    class RawConsoleVisualizer : public Visualizer {
        std::ostream& out = std::cout;
        void clearScreen() { system("clear"); }
        void drawScreen();
        void updateScreen   () override {
            clearScreen();
            drawScreen();
        }
    };
    
}


#endif
