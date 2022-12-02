#ifndef AGE_ENGINE_ENGINE_H
#define AGE_ENGINE_ENGINE_H

#include "objects/entity.h"

namespace age {
    class Sprite;
    
    class Engine {
        std::vector<Entity> entities;
        
    public:
        void update();
        std::vector<Sprite> getSprites();

    };
}

#endif
