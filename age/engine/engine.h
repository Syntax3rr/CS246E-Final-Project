#ifndef AGE_ENGINE_ENGINE_H
#define AGE_ENGINE_ENGINE_H

#include "objects/entity.h"
#include "objects/sprite.h"
#include <vector>
#include <map>
#include <string>

namespace age {
    class Sprite;

    class Engine {
        std::map<int, std::vector<Entity&>> entities;
        bool solidBorders = true;
        std::string textLines[3];
        vector<Entity> edges {
            Entity{0, 0, 0, Sprite{S_WIDTH, 1, '#'}},
            Entity{0, 0, 0, Sprite{1, C_HEIGHT + 2, '#'}},
            Entity{C_WIDTH - 1, 0, 0, Sprite{1, C_HEIGHT + 2, '#'}},
            Entity{0, C_HEIGHT + 1, 0, Sprite{S_WIDTH, 1, '#'}}
        };
        
    public:
        void update();
        void addEntity(Entity& entity);
        std::vector<Entity> getEntities();
        void setTextLine(int i, std::string text) {
            textLines[i] = text;
        };
        std::string* getTextLines() {
            return textLines;
        };
    };
}

#endif
