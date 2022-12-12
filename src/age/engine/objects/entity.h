#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include <memory>
#include "../../engine-constants.h"
#include "../../helpers/math/vec.h"
#include "../../helpers/reduce.h"
#include "../../helpers/functional-transform.h"
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
    protected:
        Vec pos;
        int z;
        Vec vel;
        vector<unique_ptr<EntityMovement>> movements;
        vector<unique_ptr<EntityCollision>> collisions;
        vector<unique_ptr<UpdateType>> updates;
        bool persistant;
        bool playerControlled; // Whether the movements vector contains player input or not.

        size_t currentState;
        vector<size_t> width, height;
        vector<Sprite> sprites;

        bool visible = true;

        const static Sprite invisibleSprite;

        Vec velBuffer = Vec{};
        Vec velStep = Vec{};
        Vec velStepBuffer = Vec{};

    public:
        int despawnTimer = 0;

        Entity(
            int x, int y, int z, Sprite sprite, bool persistant = false,
            initializer_list<UpdateType*> updates = {},
            initializer_list<EntityCollision*> collisions = {},
            initializer_list<EntityMovement*> movements = {}
        );
        Entity(
            int x, int y, int z, initializer_list<Sprite> sprites, bool persistant = false,
            initializer_list<UpdateType*> updates = {},
            initializer_list<EntityCollision*> collisions = {},
            initializer_list<EntityMovement*> movements = {}
        );
        Entity(
            int x, int y, int z, char c, bool persistant = false,
            initializer_list<UpdateType*> updates = {},
            initializer_list<EntityCollision*> collisions = {},
            initializer_list<EntityMovement*> movements = {}
        );
        Entity(const Entity& other);
        Entity(Entity&& other) noexcept;
        Entity& operator=(const Entity& other);
        Entity& operator=(Entity&& other) noexcept;

        Vec getPos() const noexcept { return pos; }
        int getZ() const noexcept { return z; }
        Vec getVel() const noexcept { return velBuffer; }

        const Sprite& getSprite() const noexcept { return visible ? sprites[currentState] : invisibleSprite; }
        size_t getWidth() const noexcept { return width[currentState]; }
        size_t getHeight() const noexcept { return height[currentState]; }
        char getAt(size_t x, size_t y) const noexcept { return visible ? sprites[currentState].getAt(x - pos.x, y - pos.y) : ' '; }

        size_t getState() const noexcept { return currentState; }

        bool checkCollision(const Entity& other) const noexcept;

        virtual bool onUpdate() { return true; };

        void update() {
            if (!onUpdate()) return;
            for (auto& update : updates) {
                update->onUpdate(*this);
            }
        }

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
        }

        void setPos(const Vec& newPos) noexcept { pos = newPos; }
        void setVel(const Vec& newVel) noexcept { vel = newVel; }
        void advanceState() noexcept {
            currentState = (currentState + 1) % sprites.size();
        }
        void setState(size_t newState);
        void stop() noexcept {
            velBuffer.reset();
            velStep.reset();
            velStepBuffer.reset();
            vel.reset();
        }

        void hide() noexcept { visible = false; }
        void show() noexcept { visible = true; }
        bool isVisible() const noexcept { return visible; }


        bool isPlayerControlled() const noexcept { return playerControlled; }
        bool isPersistant() const noexcept { return persistant; }

        virtual ~Entity() = default;
    };
}
#endif
