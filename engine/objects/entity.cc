#include "entity.h"

namespace age {
    void Entity::setState(int newState) {
        if (newState >= stateCount || newState < 0) throw std::out_of_range("Invalid state.");
        currentState = newState;
    }

    bool Entity::checkCollision(const Entity& other) const noexcept {
        if (pos.x + getWidth() <= other.pos.x) return false; // This is to the left of other.
        if (pos.x >= other.pos.x + other.getWidth()) return false; // This is to the right of other.
        if (pos.y + getHeight() <= other.pos.y) return false; // This is above other.
        if (pos.y >= other.pos.y + other.getHeight()) return false; // This is below other.
        // Check if the sprites overlap.
        // X and Y offsets
        Vec offset = pos - other.pos;

        Vec start = Vec{ std::max(0, offset.x), std::max(0, offset.y) }; // The top-left corner of the overlap.
        Vec end = Vec{ std::min(getWidth(), other.getWidth() - offset.x), std::min(getHeight(), other.getHeight() - offset.y) }; // The bottom-right corner of the overlap.

        for (int y = start.y; y < end.y; y++) {
            for (int x = start.x; x < end.x; x++) {
                if (
                    (getSprite().getAt(x, y) != NULL || getSprite().getAt(x, y) != ' ') &&
                    (other.getSprite().getAt(x - offset.x, y - offset.y) != NULL || other.getSprite().getAt(x - offset.x, y - offset.y) != ' ')
                    ) {
                    return true;
                }
            }
        }
        return false;
    }

    
}
