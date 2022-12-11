#ifndef AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPE_H
#define AGE_ENGINE_OBJECTS_UPDATE_UPDATETYPE_H
#include <vector>
#include <memory>

// Potential superclass for movement, collision, etc. types.
namespace age {
    class Entity;

    class UpdateType {
    public:
        virtual void onUpdate(Entity entity) = 0;
        virtual std::unique_ptr<UpdateType> clone() const = 0;

    };
}

#endif
