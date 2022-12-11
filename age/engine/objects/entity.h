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

        Entity(int x, int y, int z, Sprite sprite, bool persistant = false, initializer_list<EntityMovement> movements = {}, initializer_list<EntityCollision> collisions = {}, initializer_list<UpdateType> updates = {}) : 
            pos(Vec{ x, y }), z(z), vel(), movements(), persistant(persistant), playerControlled(false), currentState(0), 
            width(vector<int>{ sprite.getWidth() }), height(vector<int>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {
                this->movements.reserve(movements.size());
                for (auto& movement : movements) {
                    this->movements.push_back(unique_ptr<EntityMovement>(movement.clone()));
                    if (movement.isPlayerControlled()) playerControlled = true;
                }
            }
        
        Entity(int x, int y, int z, vector<Sprite> sprites, bool persistant = false, vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()) : 
            pos(Vec{ x, y }), z(z), vel(), movements(movements), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(), 
            [](auto  a) {return dynamic_cast<MoveByUser*> a;}) != movements.end()), currentState(0), 
            width(age::transform<Sprite, int>(sprites, [](Sprite a) {return a.getWidth();})), height(transform<Sprite, int>(sprites, [](Sprite a) {return a.getHeight();})) {}
        
        Entity(int x, int y, int z, char c, bool persistant = false, vector<unique_ptr<EntityMovement>> movements = vector<unique_ptr<EntityMovement>>()) : 
            pos(Vec{ x, y }), z(z), vel(), movements(movements), persistant(persistant), playerControlled(std::find_if(movements.begin(), movements.end(), 
            [](auto  a) {return dynamic_cast<MoveByUser*> a;}) != movements.end()), currentState(0), 
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

        void loadVelocity();
        void stepVelocity();

        void updatePosition() {
            pos += vel;
            vel.reset();
        }

        void onCollision(Entity& other);

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
