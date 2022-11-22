#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include "../../math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"

namespace age {
class Entity {
    Vec pos;
    Vec vel;
    int stateCount, currentState;
    std::vector<int> width, height;
    vector<Sprite> sprites;
public:
    Entity(int x, int y, Sprite sprite) : pos(Vec{x, y}), vel(), stateCount(1), currentState(0), width(std::vector<int>{ sprite.getWidth() }), height(std::vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {}
    Entity(int x, int y, vector<Sprite> sprites) : pos(Vec{x, y}), vel(), stateCount(sprites.size()), currentState(0), width(age::transform<Sprite, int>(sprites, [](Sprite a) 
        {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}
    Entity(int x, int y, char c) : pos(Vec{x, y}), vel(), stateCount(1), currentState(0), width(std::vector<int>{ 1 }), height(std::vector<int>{ 1 }) {}
    
    const Vec& getPos() const noexcept { return pos; }
    const Sprite& getSprite() const noexcept { return sprites[currentState]; }
    bool checkCollision(const Entity& other) const noexcept;
};
}
#endif
