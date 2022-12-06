#ifndef AGE_ENGINE_OBJECTS_TRIGGEREVENTS_TRIGGEREVENTS_H
#define AGE_ENGINE_OBJECTS_TRIGGEREVENTS_TRIGGEREVENTS_H
#include <vector>

// Potential superclass for movement, collision, etc. types.
namespace age {
    class TriggerEvent {
    public:
        virtual void onTrigger() = 0;
    };
}

#endif
