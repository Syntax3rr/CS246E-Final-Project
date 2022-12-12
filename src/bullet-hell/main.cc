#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include "../age/engine/engine.h"
#include "../age/visualizer/visualizers/curse-visualizer.h"
#include "../age/input/KeyboardInputs/curse-input.h"
#include "game/bullethell.h"

using namespace age;
using namespace bulletHell;
int main(int argc, char** argv) {
    CurseInput input;
    BulletHell engine(input);
    CurseVisualizer visualizer(engine);

    try {
        visualizer.start();
    } catch (...) {
    }
   
    return 0;
}
