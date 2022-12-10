#ifndef AGE_INPUT_INPUT_H
#define AGE_INPUT_INPUT_H
#include <map>

namespace age {
    class Input {
        std::map<char, bool> keys; // Map of keys and their states
    protected:
        void setKey(char key, bool state) { keys[key] = state; }; // Set the state of a key
        void clearKeys() { for (auto k : keys) k.second = false; } // Clear all keys
        virtual void updateKeyStates() = 0; // Update the key states
    public:
        Input() {};
        bool isPressed(char key) { return keys[key]; }; // Check if a key is pressed
        void update() { updateKeyStates(); };
    };
}

#endif
