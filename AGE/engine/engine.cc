#include "engine.h"
#include "../entities/entity.h"
#include "../entities/sprite.h"

namespace age {
    Engine::update() {
        for (auto i : entities) {
            for (auto j : i.second) {
                j->update();
            }
        }
    }

    void Engine::addEntity(Entity& entity) {
        entities[entity.getZ()].push_back(&entity);
    }

    std::vector<Entity> Engine::getEntities() {
        std::vector<Entity> sprites;
        for (auto layer = entities.rbegin(); layer != entities.rend(); ++layer) { // We want to draw sprites from the highest layer first.
            for (auto& entity : layer->second)
                sprites.push_back(*entity);
        }
        return sprites;
    }
}
