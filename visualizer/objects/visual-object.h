#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"
#include "../../math/ageobject.h"

using age::transform;
class VisualObject : public AGEObject {
    vector<Sprite> sprites;
public:
    VisualObject(int x, int y, Sprite sprite) : AGEObject(x, y, 1, vector{ sprite.getWidth() }, vector{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {}
    VisualObject(int x, int y, vector<Sprite> sprites) : AGEObject(x, y, sprites.size(), transform<Sprite, int>(sprites, [](Sprite a) 
        {return a.getWidth();}), transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}
    VisualObject(int x, int y, char c) : AGEObject(x, y, 1, vector{ 1 }, vector{ 1 }) {}
    
    const Sprite& getSprite() const noexcept { return sprites[getState()]; }
};

#endif
