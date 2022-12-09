#include "engine.h"
#include "../engine-constants.h"
#include "../helpers/math/vec.h"
#include <numeric>
#include <cmath>

namespace age {
    void Engine::update() {
        for (auto i = entities.begin(); i != entities.end(); ++i) { //Entity position update
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                Entity entity = *j;
                entity.update(); //General update call
                //Check if the entity needs to be culled
                
                while (entity.getVel() != 0) {
                    entity.stepVelocity();
                    for (auto k = j + 1; k != i->second.end(); ++k) {
                        Entity other = *k;
                        if (entity.checkCollision(other)) {
                            entity.onCollision(other);
                            other.onCollision(entity);
                        }
                    }
                    if (solidBorders || entity.playerControlled) {
                        //Check for collision with Canvas borders, which are ceneterd inside the screen borders.
                        //If going into a corner
                        if (entity.getPos().y < C_TOP) entity.onCollision(edges[0]);
                        if (entity.getPos().x < C_LEFT) entity.onCollision(edges[1]);
                        if (entity.getPos().x + entity.getWidth() > C_RIGHT) entity.onCollision(edges[3]);
                        if (entity.getPos().y + entity.getHeight() > C_BOTTOM) entity.onCollision(edges[4]);
                    } else if (entity.getPos().x < 0 || entity.getPos().y < 0 || entity.getPos().x + entity.getWidth() > C_WIDTH || entity.getPos().y + entity.getHeight() > C_HEIGHT) {
                        entity.onCollision(edges[0]);
                    }
                    entity.updatePosition();
                }
            }
        }
    }

    void Engine::addEntity(Entity& entity) {
        entities[entity.getZ()].push_back(entity);
    }

    std::vector<Entity> Engine::getEntities() {
        std::vector<Entity> sprites;
        for (auto layer = entities.rbegin(); layer != entities.rend(); ++layer) { // We want to draw sprites from the highest layer first.
            for (auto& entity : layer->second)
                sprites.push_back(entity);
        }
        return sprites;
    }
}
