#include "sprite.h"

namespace age {
    char Sprite::getAt(int x, int y) const noexcept {
        if (x < 0 || x >= width || y < 0 || y >= height) return NULL;
        return sprite[y][x];
    }
}
