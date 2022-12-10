#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include "../../age/engine/engine.h"
#include "../../age/visualizer/visualizers/raw-console-visualizer.h"
#include "../../age/engine/objects/entity.h"
#include "../../age/input/KeyboardInputs/raw-console-input.h"
#include "../../age/engine/objects/sprite.h"
#include "../../age/engine/objects/movement/entity-movement.h"
#include "../../age/engine/objects/movement/movementTypes/move-by-user.h"
#include "../../age/engine/objects/collision/entity-collision.h"
#include "../../age/engine/objects/update/update-type.h"
#include "../../age/engine/objects/update/updateTypes/cycle.h"

using namespace age;
using std::vector;
using std::make_tuple;
int main() {
    auto engine = Engine();
    //auto visualizer = RawConsoleVisualizer(engine);
    //auto input = RawConsoleInput();

    /*Entity Title = Entity(12, 5, 0, Sprite{
        make_tuple(12, 5, 'B'), make_tuple(12, 6, 'B'), make_tuple(12, 7, 'B'), make_tuple(12, 8, 'B'), make_tuple(12, 9, 'B'), make_tuple(13, 5, 'B'), make_tuple(14, 6, 'B'), make_tuple(13, 7, 'B'), make_tuple(14, 8, 'B'), make_tuple(13, 9, 'B'),
        make_tuple(17, 5, 'U'), make_tuple(17, 6, 'U'), make_tuple(17, 7, 'U'), make_tuple(17, 8, 'U'), make_tuple(17, 9, 'U'), make_tuple(19, 6, 'U'), make_tuple(19, 7, 'U'), make_tuple(19, 8, 'U'), make_tuple(18, 9, 'U'), make_tuple(19, 9, 'U'),
        make_tuple(22, 5, 'L'), make_tuple(22, 6, 'L'), make_tuple(22, 7, 'L'), make_tuple(22, 8, 'L'), make_tuple(22, 9, 'L'), make_tuple(23, 9, 'L'), make_tuple(24, 9, 'L'),
        make_tuple(27, 5, 'L'), make_tuple(27, 6, 'L'), make_tuple(27, 7, 'L'), make_tuple(27, 8, 'L'), make_tuple(27, 9, 'L'), make_tuple(28, 9, 'L'), make_tuple(28, 9, 'L'),
        make_tuple(32, 5, 'E'), make_tuple(32, 6, 'E'), make_tuple(32, 7, 'E'), make_tuple(32, 8, 'E'), make_tuple(32, 9, 'E'), make_tuple(33, 5, 'E'), make_tuple(34, 5, 'E'), make_tuple(33, 7, 'E'), make_tuple(33, 9, 'E'), make_tuple(34, 9, 'E'),
        make_tuple(37, 5, 'T'), make_tuple(38, 5, 'T'), make_tuple(39, 5, 'T'), make_tuple(38, 5, 'T'), make_tuple(38, 6, 'T'), make_tuple(38, 7, 'T'), make_tuple(38, 8, 'T'), make_tuple(38, 9, 'T'),
        make_tuple(47, 5, 'H'), make_tuple(47, 6, 'H'), make_tuple(47, 7, 'H'), make_tuple(47, 8, 'H'), make_tuple(47, 9, 'H'), make_tuple(49, 5, 'H'), make_tuple(49, 6, 'H'), make_tuple(48, 7, 'H'), make_tuple(49, 7, 'H'), make_tuple(49, 8, 'H'), make_tuple(49, 9, 'H'),
        make_tuple(52, 5, 'E'), make_tuple(52, 6, 'E'), make_tuple(52, 7, 'E'), make_tuple(52, 8, 'E'), make_tuple(52, 9, 'E'), make_tuple(53, 5, 'E'), make_tuple(54, 5, 'E'), make_tuple(53, 7, 'E'), make_tuple(53, 9, 'E'), make_tuple(54, 9, 'E'),
        make_tuple(57, 5, 'L'), make_tuple(57, 6, 'L'), make_tuple(57, 7, 'L'), make_tuple(57, 8, 'L'), make_tuple(57, 9, 'L'), make_tuple(58, 9, 'L'), make_tuple(59, 9, 'L'),
        make_tuple(62, 5, 'L'), make_tuple(62, 6, 'L'), make_tuple(62, 7, 'L'), make_tuple(62, 8, 'L'), make_tuple(62, 9, 'L'), make_tuple(63, 9, 'L'), make_tuple(64, 9, 'L') });

    Entity PAKTS = Entity(28, 5, 0, Sprite{ "Press Any Key To Start" }, false, vector<std::unique_ptr<UpdateType>>{
        std::make_unique<Cycle>(Cycle{10})
    });

    engine.addEntity(Title);
    engine.addEntity(PAKTS);*/
}
