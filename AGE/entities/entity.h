#ifndef AGE_ENTITIES_ENTITY_H
#define AGE_ENTITIES_ENTITY_H
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <memory>
#include "sprite.h"
#include "../events/event-types.h"
#include "../events/event.h"
#include <initializer_list>

namespace age {
    class Input;

    using std::vector;
    class Entity {
        int x, y, z;
        vector<Sprite> sprites;
        int state;
        bool persistent;
        std::map<EventType, vector<std::unique_ptr<Event>>> eventHandlers;
        Input* input;
        bool playerControlled = false;
    
    public:
        Entity(int x, int y, int z, Sprite& sprite, bool isPersistent = false, std::initializer_list<std::pair<EventType, Event>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            sprites.push_back(sprite);
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<Event>(event.second));

            }
        };
        Entity(int x, int y, int z, char c, bool isPersistent = false, std::initializer_list<std::pair<EventType, Event>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            sprites.push_back(Sprite(c));
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<Event>(event.second));
            }
        };
        Entity(int x, int y, int z, std::initializer_list<Sprite> sprites, bool isPersistent = false, std::initializer_list<std::pair<EventType, Event>> eventHandlers = {}, Input* input = nullptr): x(x), y(y), z(z), sprites(), state(0), persistent(isPersistent), eventHandlers(), input(input) {
            for (auto& sprite : sprites) {
                this->sprites.push_back(sprite);
            }
            
            for (auto& event : eventHandlers) {
                this->eventHandlers[event.first].push_back(std::make_unique<Event>(event.second));
            }
        };

        Entity(const Entity& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            sprites = other.sprites;
            state = other.state;
            persistent = other.persistent;
            
            for (auto& event : other.eventHandlers) {
                eventHandlers[event.first].push_back(std::make_unique<Event>(*event.second[0]));
            }
        }


        void update();
        void move(int x, int y);
        bool checkCollision(Entity& other);
        
        int getX() const noexcept { return x; }
        int getY() const noexcept { return y; }
        int getZ() const noexcept { return z; }
        void setPos(int x, int y) noexcept { this->x = x; this->y = y; }

        int getState() const noexcept { return state; }
        void setState(int state) noexcept { this->state = state; }
        void advanceState() noexcept { state = (state + 1) % sprites.size(); }

        char getAt(int x, int y) const noexcept {
            return sprites[state].getAt(x - this->x, y - this->y);
        }
        const Sprite& getSprite() { return sprites[state]; }

        bool isPersistent() const noexcept { return persistent; }

        void addEventHandler(EventType type, Event& event) {
            eventHandlers[type].push_back(std::make_unique<Event>(event));
        }

        Input* getInput() const noexcept { return input; }
    };
}

#endif
