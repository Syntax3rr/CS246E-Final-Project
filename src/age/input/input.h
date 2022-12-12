#ifndef AGE_INPUT_INPUT_H
#define AGE_INPUT_INPUT_H
#include <map>
#include <vector>
#include <ncurses.h>

namespace age {
    class Input {
        std::map<int, bool> keys; // Map of keys and their states
    protected:
        void setKey(int key, bool state) { keys[key] = state; }; // Set the state of a key
        void clearKeys() { 
            for (auto& k : keys) k.second = false; 
            } // Clear all keys
        virtual void updateKeyStates() = 0; // Update the key states
    public:
        Input() {};
        bool getKeyState(int key) { return keys[key]; }; // Get the state of a key
        void update() { updateKeyStates(); };

        std::vector<int> getPressedKeys() {
            std::vector<int> pressedKeys;
            for (auto k : keys) {
                if (k.second) pressedKeys.push_back(k.first);
            }

            return pressedKeys;
        };
    };
}

#endif
