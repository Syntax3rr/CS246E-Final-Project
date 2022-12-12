#ifndef AGE_VISUALIZER_VISUALIZERS_CURSEVISUALIZER_H
#define AGE_VISUALIZER_VISUALIZERS_CURSEVISUALIZER_H
#include <ncurses.h>
#include "../visualizer.h"

namespace age {
    class CurseVisualizer: public Visualizer {       
    public:
        CurseVisualizer(Engine& engine);
        ~CurseVisualizer();
        void updateScreen() override;
    };
}

#endif
