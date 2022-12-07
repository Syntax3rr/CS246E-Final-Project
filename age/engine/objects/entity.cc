#include "entity.h"
#include <stdexcept>
#include <numeric>
#include <cmath>

using std::gcd;
using std::abs;
namespace age {
    void Entity::setState(int newState) {
        if (newState >= stateCount || newState < 0) throw std::out_of_range("Invalid state.");
        currentState = newState;
    }

    void Entity::stepVelocity() {
        if (movements.size() && velBuffer == 0 && velStep == 0) { //If we're starting a new movement action
            for (auto& movement : movements) movement->move(velBuffer); //Get the next movements
            int velGCD = gcd(abs(velBuffer.x), abs(velBuffer.y));
            velStep = Vec{ velBuffer.x / velGCD, velBuffer.y / velGCD }; //Get the natural number step ratio.
        } else {
            if (velStepBuffer == 0) {
                velStepBuffer = velStep;
                velBuffer -= velStep;
            } else {
                if (velStepBuffer.x == velStepBuffer.y) {
                    velStepBuffer -= Vec{ 1, 1 };
                    vel += Vec{ 1, 1 };
                } else if (velStepBuffer.x > velStepBuffer.y) {
                    velStepBuffer.x--;
                    vel.x++;
                } else {
                    velStepBuffer.y--;
                    vel.y++;
                }
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
