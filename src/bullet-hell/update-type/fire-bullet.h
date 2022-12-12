#ifndef BULLETHELL_UPDATETYPE_FIREBULLET_H
#define BULLETHELL_UPDATETYPE_FIREBULLET_H
#include "../../age/engine/objects/update/update-type.h"
#include "../objects/bullet.h"
#include "../../age/helpers/math/vec.h"
#include "../../age/input/input.h"
#include "../game/bullethell.h"
#include "../../age/engine/objects/entity.h"
#include <memory>

using namespace age;

namespace bulletHell {

    class FireBullet: public UpdateType {
        BulletHell* engine;
        char bulletChar;
        Vec velocity;
        int rateOfFire;
        int frame = 0;
        Input* input;
        int fireKey;

    public:
        FireBullet(BulletHell& engine, char bulletChar, Vec velocity, int rateOfFire);
        FireBullet(BulletHell& engine, char bulletChar, Vec velocity, int rateOfFire, Input* input, int fireKey);
        FireBullet(const FireBullet& other);

        void onUpdate(Entity& entity) override;

        std::unique_ptr<UpdateType> clone() const override {
            return std::make_unique<FireBullet>(*this);
        }
    };
}

#endif
