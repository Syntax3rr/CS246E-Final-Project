#ifndef AGE_INPUT_INPUT_H
#define AGE_INPUT_INPUT_H
#include <map>
#include <vector>

namespace age {
    class Input {
        std::map<char, bool> keys; // Map of keys and their states
    protected:
        void setKey(char key, bool state) { keys[key] = state; }; // Set the state of a key
        void clearKeys() { for (auto k : keys) k.second = false; } // Clear all keys
        virtual void updateKeyStates() = 0; // Update the key states
    public:
        Input() {};
        bool getKeyState(char key) { return keys[key]; }; // Get the state of a key
        void update() { updateKeyStates(); };
        
        std::vector<char> getPressedKeys() {
            std::vector<char> pressedKeys;
            for (auto k : keys) {
                if (k.second) pressedKeys.push_back(k.first);
            }
            return pressedKeys;
        };
    };
}

#endif
