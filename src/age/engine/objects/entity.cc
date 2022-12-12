#include "entity.h"
#include <stdexcept>
#include <cmath>
#include "../../helpers/math/gcd.h"
#include <initializer_list>

namespace age {
    using std::abs;

    const Sprite Entity::invisibleSprite = Sprite{ " " };

    Entity::Entity(
        int x, int y, int z, Sprite sprite, bool persistant,
        initializer_list<UpdateType*> updates,
        initializer_list<EntityCollision*> collisions,
        initializer_list<EntityMovement*> movements
    ):
        pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(), persistant(persistant), playerControlled(reduce(movements.begin(), movements.end(), false,
            [](auto& a, bool b) {return b || a->isPlayerControlled();})), currentState(0),
        width(vector<size_t>{ sprite.getWidth() }), height(vector<size_t>{ sprite.getHeight() }), sprites(vector<Sprite>{sprite}) {
        this->updates.reserve(updates.size());
        this->collisions.reserve(collisions.size());
        this->movements.reserve(movements.size());
        for (auto& i : updates) this->updates.emplace_back(i);
        for (auto& i : collisions) this->collisions.emplace_back(i);
        for (auto& i : movements) this->movements.emplace_back(i);
    }

    Entity::Entity(
        int x, int y, int z, initializer_list<Sprite> sprites, bool persistant,
        initializer_list<UpdateType*> updates,
        initializer_list<EntityCollision*> collisions,
        initializer_list<EntityMovement*> movements
    ):
        pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(), persistant(persistant), playerControlled(reduce(movements.begin(), movements.end(), false,
            [](auto& a, bool b) {return b || a->isPlayerControlled();})), currentState(0),
        width(age::transform<Sprite, size_t>(sprites.begin(), sprites.end(), [](Sprite a) {return a.getWidth();})), height(transform<Sprite, size_t>(sprites.begin(), sprites.end(), [](Sprite a) {return a.getHeight();})) {
        this->sprites.reserve(sprites.size());
        this->updates.reserve(updates.size());
        this->collisions.reserve(collisions.size());
        this->movements.reserve(movements.size());
        for (auto& i : sprites) this->sprites.push_back(i);
        for (auto& i : updates) this->updates.emplace_back(i);
        for (auto& i : collisions) this->collisions.emplace_back(i);
        for (auto& i : movements) this->movements.emplace_back(i);
    }

    Entity::Entity(
        int x, int y, int z, char c, bool persistant,
        initializer_list<UpdateType*> updates,
        initializer_list<EntityCollision*> collisions,
        initializer_list<EntityMovement*> movements
    ):
        pos(Vec{ x, y }), z(z), vel(), movements(), collisions(), updates(),
        persistant(persistant), playerControlled(reduce(movements.begin(), movements.end(), false,
            [](auto& a, bool b) {return b || a->isPlayerControlled();})), currentState(0),
        width(vector<size_t>{ 1 }), height(vector<size_t>{ 1 }) {
        this->updates.reserve(updates.size());
        this->collisions.reserve(collisions.size());
        this->movements.reserve(movements.size());
        for (auto& i : updates) this->updates.emplace_back(i);
        for (auto& i : collisions) this->collisions.emplace_back(i);
        for (auto& i : movements) this->movements.emplace_back(i);
    }

    Entity::Entity(const Entity& other):
        pos(other.pos), z(other.z), vel(other.vel), movements(), collisions(), updates(),
        persistant(other.persistant), playerControlled(other.playerControlled), currentState(other.currentState),
        width(other.width), height(other.height), sprites(other.sprites) {
        this->updates.reserve(other.updates.size());
        this->collisions.reserve(other.collisions.size());
        this->movements.reserve(other.movements.size());
        for (auto& i : other.updates) this->updates.push_back(i->clone());
        for (auto& i : other.collisions) this->collisions.push_back(i->clone());
        for (auto& i : other.movements) this->movements.push_back(i->clone());
    }

    Entity::Entity(Entity&& other) noexcept:
        pos(other.pos), z(other.z), vel(other.vel), movements(std::move(other.movements)), collisions(std::move(other.collisions)), updates(std::move(other.updates)),
        persistant(other.persistant), playerControlled(other.playerControlled), currentState(other.currentState),
        width(other.width), height(other.height), sprites(std::move(other.sprites)) {
        other.movements.clear();
        other.collisions.clear();
        other.updates.clear();
        other.sprites.clear();
    }

    Entity& Entity::operator=(const Entity& other) {
        pos = other.pos;
        z = other.z;
        vel = other.vel;
        movements.clear();
        collisions.clear();
        updates.clear();
        persistant = other.persistant;
        playerControlled = other.playerControlled;
        currentState = other.currentState;
        width = other.width;
        height = other.height;
        sprites = other.sprites;
        this->updates.reserve(other.updates.size());
        this->collisions.reserve(other.collisions.size());
        this->movements.reserve(other.movements.size());
        for (auto& i : other.updates) this->updates.push_back(i->clone());
        for (auto& i : other.collisions) this->collisions.push_back(i->clone());
        for (auto& i : other.movements) this->movements.push_back(i->clone());
        return *this;
    }

    Entity& Entity::operator=(Entity&& other) noexcept {
        pos = other.pos;
        z = other.z;
        vel = other.vel;
        std::swap(movements, other.movements);
        std::swap(collisions, other.collisions);
        std::swap(updates, other.updates);
        std::swap(sprites, other.sprites);
        persistant = other.persistant;
        playerControlled = other.playerControlled;
        currentState = other.currentState;
        width = other.width;
        height = other.height;
        return *this;
    }

    void Entity::setState(size_t newState) {
        if (newState >= sprites.size() || newState < 0) throw std::out_of_range("Invalid state.");
        currentState = newState;
    }

    void Entity::loadVelocity() {
        if (!visible) return;
        for (auto& movement : movements) movement->move(velBuffer); //Get the next movements
        if (velBuffer == 0) return;
        int velGCD = gcd(abs(velBuffer.x), abs(velBuffer.y));
        velStep = Vec{ velBuffer.x / velGCD, velBuffer.y / velGCD }; //Get the natural number step ratio.
    }

    void Entity::stepVelocity() {
        if (velBuffer == 0) {
            velStepBuffer.reset();
            velStep.reset();
            return;
        };

        if (velStepBuffer == 0) {
            velStepBuffer = velStep;
        }

        // If the velocity is changing directions, we need to make sure that the step buffer is also changing directions.
        if ((velBuffer.x > 0 && velStepBuffer.x < 0) || (velBuffer.x < 0 && velStepBuffer.x > 0)) velStepBuffer.x = -velStepBuffer.x;
        if ((velBuffer.y > 0 && velStepBuffer.y < 0) || (velBuffer.y < 0 && velStepBuffer.y > 0)) velStepBuffer.y = -velStepBuffer.y;

        // If the velocity is shirinking, we need to make sure that the step buffer is also shrinking.
        if ((velBuffer.x < 0 && velStepBuffer.x > velBuffer.x) || (velBuffer.x > 0 && velStepBuffer.x < velBuffer.x)) velStepBuffer.x = velBuffer.x;
        if ((velBuffer.y < 0 && velStepBuffer.y > velBuffer.y) || (velBuffer.y > 0 && velStepBuffer.y < velBuffer.y)) velStepBuffer.y = velBuffer.y;

        int xDir = velStepBuffer.x > 0 ? 1 : velStepBuffer.x < 0 ? -1 : 0;
        int yDir = velStepBuffer.y > 0 ? 1 : velStepBuffer.y < 0 ? -1 : 0;

        if (std::abs(velStepBuffer.x) == std::abs(velStepBuffer.y)) {
            velStepBuffer -= Vec{ xDir, yDir };
            vel += Vec{ xDir, yDir };
            velBuffer -= Vec{ xDir, yDir };
        } else if (std::abs(velStepBuffer.x) > std::abs(velStepBuffer.y)) {
            velStepBuffer.x -= xDir;
            vel.x += xDir;
            velBuffer.x -= xDir;
        } else {
            velStepBuffer.y -= yDir;
            vel.y += yDir;
            velBuffer.y -= yDir;
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
                    (getSprite().getAt(x, y) != '\0' || getSprite().getAt(x, y) != ' ') &&
                    (other.getSprite().getAt(x - offset.x, y - offset.y) != '\0' || other.getSprite().getAt(x - offset.x, y - offset.y) != ' ')
                    ) {
                    return true;
                }
            }
        }
        return false;
    }
}
