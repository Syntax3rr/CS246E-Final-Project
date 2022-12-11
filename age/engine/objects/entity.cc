#include "entity.h"
#include <stdexcept>
#include <numeric>
#include <cmath>

using std::gcd;
using std::abs;
namespace age {
    void Entity::setState(int newState) {
        if (newState >= sprites.size() || newState < 0) throw std::out_of_range("Invalid state.");
        currentState = newState;
    }

    void Entity::loadVelocity() {
        for (auto& movement : movements) movement->move(velBuffer); //Get the next movements
        int velGCD = gcd(abs(velBuffer.x), abs(velBuffer.y));
        velStep = Vec{ velBuffer.x / velGCD, velBuffer.y / velGCD }; //Get the natural number step ratio.
    }

    void Entity::stepVelocity() {
        if (velBuffer == 0) return;

        if (velStepBuffer == 0) {
            velStepBuffer = velStep;
        } else {
            // If the velocity is changing directions, we need to make sure that the step buffer is also changing directions.
            if (velBuffer.x > 0 && velStepBuffer.x < 0 || velBuffer.x < 0 && velStepBuffer.x > 0) velStepBuffer.x = -velStepBuffer.x;
            if (velBuffer.y > 0 && velStepBuffer.y < 0 || velBuffer.y < 0 && velStepBuffer.y > 0) velStepBuffer.y = -velStepBuffer.y;

            // If the velocity is shirinking, we need to make sure that the step buffer is also shrinking.
            if (velBuffer.x < 0 && velStepBuffer.x > velBuffer.x || velBuffer.x > 0 && velStepBuffer.x < velBuffer.x) velStepBuffer.x = velBuffer.x;
            if (velBuffer.y < 0 && velStepBuffer.y > velBuffer.y || velBuffer.y > 0 && velStepBuffer.y < velBuffer.y) velStepBuffer.y = velBuffer.y;

            if (velStepBuffer.x == velStepBuffer.y) {
                velStepBuffer -= Vec{ 1, 1 };
                vel += Vec{ 1, 1 };
                velBuffer -= Vec{ 1, 1 };
            } else if (velStepBuffer.x > velStepBuffer.y) {
                velStepBuffer.x--;
                vel.x++;
                velBuffer.x--;
            } else {
                velStepBuffer.y--;
                vel.y++;
                velBuffer.y--;
            }
        }
    }

    bool Entity::checkCollision(const Entity& other) const noexcept {
        if ( // Fast check to see if the sprites can possibly overlap.
            z != other.z || // Different z-levels.
            pos.x + getWidth() <= other.pos.x || // This is to the left of other.
            pos.x >= other.pos.x + other.getWidth() || // This is to the right of other.
            pos.y + getHeight() <= other.pos.y || // This is above other.
            pos.y >= other.pos.y + other.getHeight() // This is below other.
            ) return false;

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
