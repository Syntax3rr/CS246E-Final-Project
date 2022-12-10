#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include <memory>
#include <algorithm>
#include "../../engine-constants.h"
#include "../../helpers/math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"
#include "movement/entity-movement.h"
#include "collision/entity-collision.h"
#include "update/update-type.h"

using std::vector;
using std::unique_ptr;
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
        const bool playerControlled; // Whether the movements vector contains player input or not.

    private:
        int stateCount, currentState;
        vector<int> width, height;
        vector<Sprite> sprites;

        bool visible = true;

        Vec velBuffer = Vec{};
        Vec velStep = Vec{};
        Vec velStepBuffer = Vec{};

    public:
        int despawnTimer = 0; //I could make engine a friend, but honestly it doesn't matter for this.

        Entity(
            int x, int y, int z, Sprite sprite, bool persistant = false,
            vector<unique_ptr<UpdateType>> updates = vector<unique_ptr<UpdateType>>(),
            vector<unique_ptr<EntityCollision>> collisions = vector<unique_ptr<EntityCollision>>(),
            vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(movements), collisions(collisions), updates(updates), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(),
                [](auto  a) {return dynamic_cast<MoveByUser*>(a);}) != movements.end()), stateCount(1), currentState(0),
            width(vector<int>{ sprite.getWidth() }), height(vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {}

        Entity(
            int x, int y, int z, vector<Sprite> sprites, bool persistant = false,
            vector<unique_ptr<UpdateType>> updates = vector<unique_ptr<UpdateType>>(),
            vector<unique_ptr<EntityCollision>> collisions = vector<unique_ptr<EntityCollision>>(),
            vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(movements), collisions(collisions), updates(updates), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(),
                [](auto  a) {return dynamic_cast<MoveByUser*>(a);}) != movements.end()), stateCount(sprites.size()), currentState(0),
            width(age::transform<Sprite, int>(sprites, [](Sprite a) {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}

        Entity(
            int x, int y, int z, char c, bool persistant = false,
            vector<unique_ptr<UpdateType>> updates = vector<unique_ptr<UpdateType>>(),
            vector<unique_ptr<EntityCollision>> collisions = vector<unique_ptr<EntityCollision>>(),
            vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()
        ):
            pos(Vec{ x, y }), z(z), vel(), movements(movements), collisions(collisions), updates(updates),
            persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(),
                [](auto  a) {return dynamic_cast<MoveByUser*>(a);}) != movements.end()), stateCount(1), currentState(0),
            width(vector<int>{ 1 }), height(vector<int>{ 1 }) {}

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
            currentState = (currentState + 1) % stateCount;
        }
        void setState(int newState);
        void stop() noexcept {
            velBuffer.reset();
            velStep.reset();
            velStepBuffer.reset();
            vel.reset();
        }
    };
}
#endif
