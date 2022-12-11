#include "engine.h"
#include "../engine-constants.h"
#include "../helpers/math/vec.h"
#include <numeric>
#include <map>
#include <cmath>
#include <utility>
namespace age {
    void Engine::update() {
        input->update();
        onUpdate();
        for (auto i = entities.begin(); i != entities.end(); ++i) { // Load Enitity Velocities
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                Entity& entity = **j;
                entity.update(); //General update call
                entity.loadVelocity();
            }
        }

        for (auto i = entities.begin(); i != entities.end(); ++i) { //Entity position update
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                Entity& entity = **j;

                while (entity.getVel() != 0) {
                    int x = entity.getPos().x;
                    int y = entity.getPos().y;
                    int width = entity.getWidth();
                    int height = entity.getHeight();
                    bool timeoutCheck = false;

                    entity.stepVelocity();
                    for (auto k = j + 1; k != i->second.end(); ++k) {
                        Entity& other = **k;
                        if (entity.checkCollision(other)) {
                            entity.onCollision(other);
                            other.onCollision(entity);
                        }
                    }

                    if (solidBorders || entity.isPlayerControlled()) {
                        //Check for collision with Canvas borders, which are ceneterd inside the screen borders.
                        if (y < C_TOP) entity.onCollision(edges[0]);
                        if (x < C_LEFT) entity.onCollision(edges[1]);
                        if (x + width > C_RIGHT) entity.onCollision(edges[3]);
                        if (y + height > C_BOTTOM) entity.onCollision(edges[4]);
                    } else if (!timeoutCheck && (x < 0 || y < 0 || x + width > C_WIDTH || y + height > C_HEIGHT)) {
                        if (!entity.isPersistant() && ++(entity.despawnTimer) > DESPAWN_TIME) {
                            i->second.erase(j);
                            break;
                        }
                        timeoutCheck = true;
                    } else {
                        entity.despawnTimer = timeoutCheck ? entity.despawnTimer : 0;
                    }
                    entity.updatePosition();
                }
            }
        }
    }

    void Engine::addEntity(Entity& entity) {
        entities[entity.getZ()].push_back(&entity);
    }

    std::vector<Entity*> Engine::getEntities() {
        std::vector<Entity*> output;
        for (auto& i : entities) { // Higher number -> Higher layer
            for (auto j : i.second) {
                output.push_back(j);
            }
        }
        return output;
    }
}
