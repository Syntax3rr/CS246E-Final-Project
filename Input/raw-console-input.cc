#include "raw-console-input.h"


namespace age {
    void RawConsoleInput::updateKeyStates() {
        clearKeys();
        char key;
        while (std::async([key, input]() {input >> key})) {
            setKey(key, true);
        }
    }

    char RawConsoleInput::getInput() {
        return std::getLine(input);
    }

}
