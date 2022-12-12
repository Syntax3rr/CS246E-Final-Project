#ifndef BULLETHELL_OBJECTS_ENEMY_H
#define BULLETHELL_OBJECTS_ENEMY_H
#include "../../age/engine/objects/entity.h"
#include "../../age/helpers/math/vec.h"
#include <initializer_list>

namespace bulletHell {
    using namespace age;
    using std::initializer_list;
    class BulletHell;
    class Enemy: public Entity {
    protected:
        int health = 1;
    public:
        Enemy(BulletHell& engine, Vec pos, char c = 's', int health = 1, initializer_list<EntityMovement*> movement = {}, initializer_list<EntityMovement*> bulletTrajectory = {}, int rateOfFire = 10);

        Enemy(BulletHell& engine, Vec pos, char c = 's', int health = 1, initializer_list<EntityMovement*> movement = {}, int rateOfFire = 10);

        int getHealth() { return health; }

        void damage(int damage = 1);
    };
}

#endif
