#include "engine.h"
#include "../helpers/math/vec.h"

namespace age {
    void Engine::update() {
        for (auto i = entities.begin(); i != entities.end(); ++i) { //Entity position update
            Entity entity = *i;
            entity.update();
            while (entity.getVel() != 0) {
                entity.stepVelocity();
                for (auto j = i + 1; j != entities.end(); ++j) {
                    Entity other = *j;
                    if (entity.checkCollision(other)) {
                        entity.onCollision(other);
                        other.onCollision(entity);
                    }
                }
                entity.updatePosition();
            }
        }
    }

    std::vector<Sprite> Engine::getSprites() {
        std::vector<Sprite> sprites;
        for (auto& entity : entities) {
            sprites.push_back(entity.getSprite());
        }
        return sprites;
    }
}
