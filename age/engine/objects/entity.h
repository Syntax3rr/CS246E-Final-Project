#ifndef AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#define AGE_VISUALIZER_OBJECTS_VISUALOBJECT_H
#include <vector>
#include <memory>
#include <algorithm>
#include "../../helpers/math/vec.h"
#include "../../helpers/functional-vector-transform.h"
#include "sprite.h"
#include "movement/entity-movement.h"

using std::vector;
using std::unique_ptr;
namespace age {
    struct MoveByUser;
    
    class Entity {
        Vec pos;
        int z;
        Vec vel;
        vector<unique_ptr<EntityMovement>> movements;

    public:
        const bool persistant;
        const bool playerControlled; // Whether the movements vector contains player input or not.
    
    private:
        int stateCount, currentState;
        vector<int> width, height;
        vector<Sprite> sprites;

        Vec velBuffer = Vec{};
        Vec velStep = Vec{};
        Vec velStepBuffer = Vec{};

    public:
        Entity(int x, int y, int z, Sprite sprite, bool persistant = false, vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()) : 
            pos(Vec{ x, y }), z(z), vel(), movements(movements), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(), 
            [](auto  a) {return dynamic_cast<MoveByUser*> a;}) != movements.end()), stateCount(1), currentState(0), 
            width(vector<int>{ sprite.getWidth() }), height(vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {}
        
        Entity(int x, int y, int z, vector<Sprite> sprites, bool persistant = false, vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()) : 
            pos(Vec{ x, y }), z(z), vel(), movements(movements), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(), 
            [](auto  a) {return dynamic_cast<MoveByUser*> a;}) != movements.end()), stateCount(sprites.size()), currentState(0), 
            width(age::transform<Sprite, int>(sprites, [](Sprite a) {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}
        
        Entity(int x, int y, int z, char c, bool persistant = false, vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()) : 
            pos(Vec{ x, y }), z(z), vel(), movements(movements), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(), 
            [](auto  a) {return dynamic_cast<MoveByUser*> a;}) != movements.end()), stateCount(1), currentState(0), 
            width(vector<int>{ 1 }), height(vector<int>{ 1 }) {}

        Vec getPos() const noexcept { return pos; }
        int getZ() const noexcept { return z; }
        Vec getVel() const noexcept { return vel; }
        const Sprite& getSprite() const noexcept { return sprites[currentState]; }
        int getWidth() const noexcept { return width[currentState]; }
        int getHeight() const noexcept { return height[currentState]; }
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
