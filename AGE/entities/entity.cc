#include "entity.h"
#include <cmath>
#include <numeric>

namespace age {
    void Entity::update() {
        for (auto& event : eventHandlers[EventType::STATE]) {
            event->onEvent();
        }
    }

    bool Entity::checkCollision(int vx, int vy, const Entity& other) const {
        int x = this->x + vx;
        int y = this->y + vy;

        if ( // Fast check to see if the sprites can possibly overlap.
            z != other.z || // Different z-levels.
            x + getWidth() <= other.x || // This is to the left of other.
            x >= other.x + other.getWidth() || // This is to the right of other.
            y + getHeight() <= other.y || // This is above other.
            y >= other.y + other.getHeight() // This is below other.
            ) return false;

        // Check if the sprites overlap.
        // X and Y offsets
        int xOffset = x - other.x;
        int yOffset = y - other.y;

        int xStart = std::max(0, xOffset); // The top-left corner of the overlap.
        int yStart = std::max(0, yOffset);
        int xEnd = std::min(getWidth(), other.getWidth() - xOffset); // The bottom-right corner of the overlap.
        int yEnd = std::min(getHeight(), other.getHeight() - yOffset);

        for (int y = yStart; y < yEnd; y++) { // Check each character in the overlap.
            for (int x = xStart; x < xEnd; x++) {
                if (
                    (getAtRel(x, y) != '\0' || getAtRel(x, y) != ' ') &&
                    (other.getAtRel(x - xOffset, y - yOffset) != '\0' || other.getAtRel(x - xOffset, y - yOffset) != ' ')
                    ) {
                    return true;
                }
            }
        }
        return false;
    }

    std::pair<int,int> Entity::nextStep() {
        if (vx == 0 && vy == 0) {
            return std::pair<int,int>{ 0, 0 };
            rx = ry = sx = sy = 0;
        }

        // Calculate the slope of motion
        if (rx == 0 && ry == 0) {
            int gcd = std::gcd(std::abs(vx), std::abs(vy));

            rx = vx / gcd;
            ry = vy / gcd;
        }

        // Check for velocity inversions
        if (vx > 0 && rx < 0 || vx < 0 && rx > 0) {
            rx *= -1;
            sx *= -1;
        }
        if (vy > 0 && ry < 0 || vy < 0 && ry > 0) { 
            ry *= -1;
            sy *= -1;
        }

        // Check for Velocity Reduction
        if (vx < rx) rx = vx;
        if (vy < ry) ry = vy;

        // Precalculate the signs
        int xSign = vx > 0 ? 1 : -1;
        int ySign = vy > 0 ? 1 : -1;

        // Finshed current slope section.
        if (rx == sx && ry == sy) {
            sx = sy = 0;
        }

        // Return step
        if (rx - sx == ry - sy) {
            sx += xSign;
            sy += ySign;
            vx -= xSign; vy -= ySign;
            rx -= xSign; ry -= ySign;
            return std::pair<int,int>{ xSign, ySign };
        } else if (rx - sx > ry - sy) {
            sx += xSign;
            vx -= xSign; rx -= xSign;
            return std::pair<int,int>{ xSign, 0 };
        } else {
            sy += ySign;
            vy -= ySign; ry -= ySign;
            return std::pair<int,int>{ 0, 1 };
        }


    }
}
