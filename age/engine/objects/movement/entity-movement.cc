#include "entity-movement.h"
#include "../../helpers/math/vec.h"

namespace age {
    Vec& EntityMovement::move(Vec& vel) { // Default implementation: Do nothing
        return vel;
    }
}
