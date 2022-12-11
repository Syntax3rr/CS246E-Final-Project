#ifndef AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#define AGE_ENGINE_OBJECTS_MOVEMENT_ENTITYMOVEMENT_H
#include "../../../helpers/math/vec.h"
#include <memory>

namespace age {
    struct EntityMovement {
        virtual Vec& move(Vec& vel) = 0;

        virtual const bool isPlayerControlled() const { return false; }

        virtual std::unique_ptr<EntityMovement> clone() const = 0;

        virtual ~EntityMovement() {}
    };
}

#endif
