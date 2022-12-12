#ifndef AGE_ENGINE_ENGINE_H
#define AGE_ENGINE_ENGINE_H

#include "objects/entity.h"
#include "objects/sprite.h"
#include "../input/input.h"
#include <vector>
#include <map>
#include <string>
#include <initializer_list>

namespace age {
    class Sprite;

    class Engine {
    protected:
        std::map<int, std::vector<Entity*>> entities;
        std::string textLines[3];
    public:
        Input* const input;
    private:
        bool solidBorders = true;

        vector<Entity> edges {
            Entity{0, 0, 0, Sprite{S_WIDTH, 1, '#'}},
            Entity{0, 0, 0, Sprite{1, C_HEIGHT + 2, '#'}},
            Entity{C_WIDTH - 1, 0, 0, Sprite{1, C_HEIGHT + 2, '#'}},
            Entity{0, C_HEIGHT + 1, 0, Sprite{S_WIDTH, 1, '#'}}
        };
        
    protected:
        virtual void onUpdate() {};

    public:
        Engine(Input& input, bool solidBorders = false);

        void update();

        void addEntity(Entity* entity);
        std::vector<Entity*> getEntities();

        void setTextLine(int i, std::string text) { textLines[i] = text; };
        std::string* getTextLines() { return textLines; };
    };
}

#endif
