#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../age/engine/engine.h"
#include "../../age/visualizer/visualizers/raw-console-visualizer.h"
#include "../../age/engine/objects/entity.h"
#include "../../age/input/KeyboardInputs/raw-console-input.h"
#include "../../age/engine/objects/movement/movementTypes/move-by-user.h"

using namespace age;
using std::vector;
int main() {
    auto engine = Engine();
    auto visualizer = RawConsoleVisualizer(engine);
    auto input = RawConsoleInput();

    auto player = Entity(0, 0, 0, 'X', true, vector{std::make_unique<MoveByUser>(MoveByUser(input))});
    
    engine.addEntity(player);
}
