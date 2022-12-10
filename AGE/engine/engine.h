#ifndef AGE_ENGINE_ENGINE_H
#define AGE_ENGINE_ENGINE_H
#include <vector>
#include <map>

namespace age {
    class Engine {
        std::map<int, std::vector<Entity*>> entities; //Entities by z-index
        bool solidBorders = true;
        std::string textLines[3];
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
