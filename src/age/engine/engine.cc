#include "engine.h"
#include "../engine-constants.h"
#include "../helpers/math/vec.h"
#include <numeric>
#include <map>
#include <cmath>
#include <utility>
namespace age {
    Engine::Engine(Input& input, bool solidBorders): entities(), textLines{""}, input(&input), solidBorders(solidBorders) {}

    void Engine::update() {
        input->update();
        onUpdate();
        for (auto i = entities.begin(); i != entities.end(); ++i) { // Load Enitity Velocities
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                Entity& entity = **j;

                //Despawn entities that are out of bounds
                if (entity.getPos().x < 0 || entity.getPos().y < 0 || entity.getPos().x + entity.getWidth() > C_WIDTH || entity.getPos().y + entity.getHeight() > C_HEIGHT) {
                    if (!entity.isPersistant() && (++(entity.despawnTimer) > DESPAWN_TIME || entity.getPos().length() > 200) ) { // If out of bounds for 10 frames or far enough away, despawn. (length() > X is from the top-left corner, but at that point it's probably not worth keeping track of regardless)
                        i->second.erase(j);
                        break;
                    }
                } else {
                    entity.despawnTimer = 0;
                }

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
                    }

                    entity.updatePosition();
                }
            }
        }
    }

    void Engine::addEntity(Entity* entity) {
        entities[entity->getZ()].push_back(entity);
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
