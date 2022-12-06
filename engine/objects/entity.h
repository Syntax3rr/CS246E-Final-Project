#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include <numeric>
#include <cmath>
#include "../../helpers/math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"
#include "entity-movement.h"

using std::vector;
using std::gcd;
using std::abs;
namespace age {
    class Entity {
        Vec pos;
        Vec vel;
        vector<EntityMovement> movements;

        int stateCount, currentState;
        vector<int> width, height;
        vector<Sprite> sprites;

        Vec velBuffer = Vec{};
        Vec velStep = Vec{};
        Vec velStepBuffer = Vec{};

    public:
        Entity(int x, int y, Sprite sprite, vector<EntityMovement> movements) : pos(Vec{ x, y }), vel(), movements(movements), stateCount(1), currentState(0), width(vector<int>{ sprite.getWidth() }), height(vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {}
        Entity(int x, int y, vector<Sprite> sprites, vector<EntityMovement> movements) : pos(Vec{ x, y }), vel(), movements(movements), stateCount(sprites.size()), currentState(0), width(age::transform<Sprite, int>(sprites, [](Sprite a) {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}
        Entity(int x, int y, char c, vector<EntityMovement> movements) : pos(Vec{ x, y }), vel(), movements(movements), stateCount(1), currentState(0), width(vector<int>{ 1 }), height(vector<int>{ 1 }) {}

        const Vec getPos() const noexcept { return pos; }
        const Vec getVel() const noexcept { return vel; }
        const Sprite getSprite() const noexcept { return sprites[currentState]; }
        const int getWidth() const noexcept { return width[currentState]; }
        const int getHeight() const noexcept { return height[currentState]; }
        bool checkCollision(const Entity& other) const noexcept;

        void update() {};

        void stepVelocity();

        void updatePosition() {
            pos += vel;
            vel.reset();
        }

        void onCollision(Entity& other);

        void setPos(const Vec& newPos) noexcept { pos = newPos; }
        void setVel(const Vec& newVel) noexcept { vel = newVel; }
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
