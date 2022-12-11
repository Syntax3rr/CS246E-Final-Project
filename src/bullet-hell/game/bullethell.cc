#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include "../../age/engine/engine.h"
#include "../../age/visualizer/visualizers/curse-visualizer.h"
#include "../../age/engine/objects/entity.h"
#include "../../age/input/KeyboardInputs/curse-input.h"
#include "../../age/engine/objects/sprite.h"
#include "../../age/engine/objects/movement/entity-movement.h"
#include "../../age/engine/objects/movement/movementTypes/move-by-user.h"
#include "../../age/engine/objects/collision/entity-collision.h"
#include "../../age/engine/objects/update/update-type.h"
#include "../../age/engine/objects/update/updateTypes/cycle.h"

using namespace age;
using std::vector;
using std::make_tuple;
int main(int argc, char** argv) {
    CurseInput input;
    Engine engine(input, true);
    CurseVisualizer visualizer(engine);

    Entity Title = Entity(12, 5, 0, Sprite{
        make_tuple(0, 0, 'B'), make_tuple(0, 1, 'B'), make_tuple(0, 2, 'B'), make_tuple(0, 3, 'B'), make_tuple(0, 4, 'B'), make_tuple(1, 0, 'B'), make_tuple(2, 1, 'B'), make_tuple(1, 2, 'B'), make_tuple(2, 3, 'B'), make_tuple(1, 4, 'B'),
        make_tuple(5, 0, 'U'), make_tuple(5, 1, 'U'), make_tuple(5, 2, 'U'), make_tuple(5, 3, 'U'), make_tuple(5, 4, 'U'), make_tuple(7, 0, 'U'), make_tuple(7, 1, 'U'), make_tuple(7, 2, 'U'), make_tuple(7, 3, 'U'), make_tuple(6, 4, 'U'), make_tuple(7, 4, 'U'),
        make_tuple(10, 0, 'L'), make_tuple(10, 1, 'L'), make_tuple(10, 2, 'L'), make_tuple(10, 3, 'L'), make_tuple(10, 4, 'L'), make_tuple(11, 4, 'L'), make_tuple(12, 4, 'L'),
        make_tuple(15, 0, 'L'), make_tuple(15, 1, 'L'), make_tuple(15, 2, 'L'), make_tuple(15, 3, 'L'), make_tuple(15, 4, 'L'), make_tuple(16, 4, 'L'), make_tuple(16, 4, 'L'),
        make_tuple(20, 0, 'E'), make_tuple(20, 1, 'E'), make_tuple(20, 2, 'E'), make_tuple(20, 3, 'E'), make_tuple(20, 4, 'E'), make_tuple(21, 0, 'E'), make_tuple(22, 0, 'E'), make_tuple(21, 2, 'E'), make_tuple(21, 4, 'E'), make_tuple(22, 4, 'E'),
        make_tuple(25, 0, 'T'), make_tuple(26, 0, 'T'), make_tuple(27, 0, 'T'), make_tuple(26, 0, 'T'), make_tuple(26, 1, 'T'), make_tuple(26, 2, 'T'), make_tuple(26, 3, 'T'), make_tuple(26, 4, 'T'),
        make_tuple(35, 0, 'H'), make_tuple(35, 1, 'H'), make_tuple(35, 2, 'H'), make_tuple(35, 3, 'H'), make_tuple(35, 4, 'H'), make_tuple(37, 0, 'H'), make_tuple(37, 1, 'H'), make_tuple(36, 2, 'H'), make_tuple(37, 2, 'H'), make_tuple(37, 3, 'H'), make_tuple(37, 4, 'H'),
        make_tuple(40, 0, 'E'), make_tuple(40, 1, 'E'), make_tuple(40, 2, 'E'), make_tuple(40, 3, 'E'), make_tuple(40, 4, 'E'), make_tuple(41, 0, 'E'), make_tuple(42, 0, 'E'), make_tuple(41, 2, 'E'), make_tuple(41, 4, 'E'), make_tuple(42, 4, 'E'),
        make_tuple(45, 0, 'L'), make_tuple(45, 1, 'L'), make_tuple(45, 2, 'L'), make_tuple(45, 3, 'L'), make_tuple(45, 4, 'L'), make_tuple(46, 4, 'L'), make_tuple(47, 4, 'L'),
        make_tuple(50, 0, 'L'), make_tuple(50, 1, 'L'), make_tuple(50, 2, 'L'), make_tuple(50, 3, 'L'), make_tuple(50, 4, 'L'), make_tuple(51, 4, 'L'), make_tuple(52, 4, 'L') });


    
    Entity PAKTS = Entity(28, 15, 0, {Sprite{ "Press Any Key To Start" }, Sprite{' '}}, false, {
        new Cycle(3000)
    });
    
    engine.addEntity(Title);
    engine.addEntity(PAKTS);

    engine.attachUpdateFunction([](Engine& engine) {
        std::vector<char> keys = (engine.input)->getPressedKeys();
        engine.setTextLine(1, std::string(keys.begin(), keys.end()));
        engine.setTextLine(2, engine.getTextLines()[0]);
    });

    visualizer.start();
    return 0;
}
