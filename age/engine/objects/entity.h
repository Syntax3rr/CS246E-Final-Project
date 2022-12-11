#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include <memory>
#include <numeric>
#include "../../engine-constants.h"
#include "../../helpers/math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"
#include "movement/entity-movement.h"
#include "collision/entity-collision.h"
#include "update/update-type.h"
#include <initializer_list>

using std::vector;
using std::unique_ptr;
using std::initializer_list;
namespace age {
    struct MoveByUser;

    class Entity {
        Vec pos;
        int z;
        Vec vel;
        vector<unique_ptr<EntityMovement>> movements;
        vector<unique_ptr<EntityCollision>> collisions;
        vector<unique_ptr<UpdateType>> updates;

    public:
        const bool persistant;

    private:
        bool playerControlled; // Whether the movements vector contains player input or not.

        int currentState;
        vector<int> width, height;
        vector<Sprite> sprites;

        bool visible = true;

        Vec velBuffer = Vec{};
        Vec velStep = Vec{};
        Vec velStepBuffer = Vec{};

    public:
        int despawnTimer = 0;

        Entity(
            int x, int y, int z, Sprite sprite, bool persistant = false,
            initializer_list<unique_ptr<UpdateType>> updates = {},
            initializer_list<unique_ptr<EntityCollision>> collisions = {},
            initializer_list<unique_ptr<EntityMovement>> movements = {}
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(), persistant(persistant), playerControlled(std::reduce(movements.begin(), movements.end(), false,
                [](auto a, bool b) {return b || a.isPlayerControlled();})), currentState(0),
            width(vector<int>{ sprite.getWidth() }), height(vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {
            this->updates.reserve(updates.size());
            this->collisions.reserve(collisions.size());
            this->movements.reserve(movements.size());
            for (auto& i : updates) this->updates.push_back(i->clone());
            for (auto& i : collisions) this->collisions.push_back(i->clone());
            for (auto& i : movements) this->movements.push_back(i->clone());
        }

        Entity(
            int x, int y, int z, vector<Sprite> sprites, bool persistant = false,
            initializer_list<unique_ptr<UpdateType>> updates = {},
            initializer_list<unique_ptr<EntityCollision>> collisions = {},
            initializer_list<unique_ptr<EntityMovement>> movements = {}
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(), persistant(persistant), playerControlled(std::reduce(movements.begin(), movements.end(), false,
                [](auto a, bool b) {return b || a.isPlayerControlled();})), currentState(0),
            width(age::transform<Sprite, int>(sprites, [](Sprite a) {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {
            this->updates.reserve(updates.size());
            this->collisions.reserve(collisions.size());
            this->movements.reserve(movements.size());
            for (auto& i : updates) this->updates.push_back(i->clone());
            for (auto& i : collisions) this->collisions.push_back(i->clone());
            for (auto& i : movements) this->movements.push_back(i->clone());
        }

        Entity(
            int x, int y, int z, char c, bool persistant = false,
            initializer_list<unique_ptr<UpdateType>> updates = {},
            initializer_list<unique_ptr<EntityCollision>> collisions = {},
            initializer_list<unique_ptr<EntityMovement>> movements = {}
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(),
            persistant(persistant), playerControlled(std::reduce(movements.begin(), movements.end(), false,
                [](auto a, bool b) {return b || a.isPlayerControlled();})), currentState(0),
            width(vector<int>{ 1 }), height(vector<int>{ 1 }) {
            this->updates.reserve(updates.size());
            this->collisions.reserve(collisions.size());
            this->movements.reserve(movements.size());
            for (auto& i : updates) this->updates.push_back(i->clone());
            for (auto& i : collisions) this->collisions.push_back(i->clone());
            for (auto& i : movements) this->movements.push_back(i->clone());
        }

        Vec getPos() const noexcept { return pos; }
        int getZ() const noexcept { return z; }

        Vec getVel() const noexcept { return vel; }

        const Sprite& getSprite() const noexcept { return sprites[currentState]; }
        int getWidth() const noexcept { return width[currentState]; }
        int getHeight() const noexcept { return height[currentState]; }

        int getState() const noexcept { return currentState; }

        bool checkCollision(const Entity& other) const noexcept;

        void update() {
            for (auto& update : updates) {
                update->onUpdate(*this);
            }
        };

        void loadVelocity();
        void stepVelocity();

        void updatePosition() {
            pos += vel;
            vel.reset();
        }

        void onCollision(Entity& other) {
            for (auto& collision : collisions) {
                collision->onCollision(*this, other);
            }
        };

        void setPos(const Vec& newPos) noexcept { pos = newPos; }
        void setVel(const Vec& newVel) noexcept { vel = newVel; }
        void advanceState() noexcept {
            currentState = (currentState + 1) % sprites.size();
        }
        void setState(int newState);
        void stop() noexcept {
            velBuffer.reset();
            velStep.reset();
            velStepBuffer.reset();
            vel.reset();
        }

        bool isPlayerControlled() const noexcept { return playerControlled; }
    };
}
#endif
