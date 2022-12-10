#ifndef AGE_ENTITIES_ENTITY_H
#define AGE_ENTITIES_ENTITY_H
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <memory>
#include "sprite.h"
#include "../update-events/event-types.h"
#include "../update-events/update-event.h"
#include "collision/collision-base.h"
#include <initializer_list>

namespace age {
    class Input;

    using std::vector;
    class Entity {
        int x, y, z;
        vector<Sprite> sprites;
        int state;
        bool persistent;
        std::map<EventType, vector<std::unique_ptr<UpdateEvent>>> eventHandlers;
        vector<CollisionBase> collisionEvents;
        Input* input;
        bool playerControlled = false;

        int vx = 0, vy = 0; // Velocity
        int rx = 0, ry = 0; // Ratio, for smooth movement
        int sx = 0, sy = 0; // Steps, used to keep track of how many steps have been taken relative to the ratio
    
    public:
        Entity(int x, int y, int z, Sprite& sprite, bool isPersistent = false, std::initializer_list<std::pair<EventType, UpdateEvent>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            sprites.push_back(sprite);
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<UpdateEvent>(event.second));

            }
        };
        Entity(int x, int y, int z, char c, bool isPersistent = false, std::initializer_list<std::pair<EventType, UpdateEvent>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            sprites.push_back(Sprite(c));
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<UpdateEvent>(event.second));
            }
        };
        Entity(int x, int y, int z, std::initializer_list<Sprite> sprites, bool isPersistent = false, std::initializer_list<std::pair<EventType, UpdateEvent>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            for (auto& sprite : sprites) {
                this->sprites.push_back(sprite);
            }
            
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<UpdateEvent>(event.second));
            }
        };

        Entity(const Entity& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            sprites = other.sprites;
            state = other.state;
            persistent = other.persistent;
            
            for (auto& eventList : other.eventHandlers) {
                for (auto& event : eventList.second) {
                    eventHandlers[eventList.first].push_back(std::make_unique<UpdateEvent>((event->clone()).initialize(this)))
                }
            }
        }


        void update();
        void move(int vx, int vy) {
            this->vx += vx;
            this->vy += vy;
        }
        std::pair<int,int> nextStep();
        bool checkCollision(int vx, int vy, const Entity& other) const; // Check if this entity at a future position collides with another entity
        
        int getX() const noexcept { return x; }
        int getY() const noexcept { return y; }
        int getZ() const noexcept { return z; }
        void setPos(int x, int y) noexcept { this->x = x; this->y = y; }

        int getHeight() const noexcept { return sprites[state].getHeight(); }
        int getWidth() const noexcept { return sprites[state].getWidth(); }

        int getState() const noexcept { return state; }
        void setState(int state) noexcept { this->state = state; }
        void advanceState() noexcept { state = (state + 1) % sprites.size(); }

        char getAt(int x, int y) const noexcept {
            return sprites[state].getAt(x - this->x, y - this->y);
        }
        char getAtRel(int x, int y) const noexcept {
            return sprites[state].getAt(x, y);
        }

        const Sprite& getSprite() { return sprites[state]; }

        bool isPersistent() const noexcept { return persistent; }

        void addEventHandler(EventType type, UpdateEvent& event) {
            eventHandlers[type].push_back(std::make_unique<UpdateEvent>(event));
        }

        Input* getInput() const noexcept { return input; }
    };
}

#endif
