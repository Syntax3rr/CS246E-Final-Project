#ifndef AGE_HELPERS_MATH_RAYCAST_H
#define AGE_HELPERS_MATH_RAYCAST_H
#include <vector>
#include <cmath>
#include <algorithm>
#include "vec.h"

namespace age {
    struct RaycastData {
        Vec hit; // The map index of where the raycast hit.
        Vec normal; // The side the raycast hit.
        Vec adjustedVel; // The velocity adjusted to not hit the raycast.
    };

    const RaycastData& raycast(const Vec& pos, const Vec& dir, const std::vector<std::vector<char>> map, const Vec& mapOffset = Vec{0, 0});
}
