#include "raw-console-input.h"

namespace age {
    RawConsoleInput::RawConsoleInput() : prevSettings(termios{}) {
        struct termios settings = termios{};
        tcgetattr(0, &prevSettings);
        tcgetattr(0, &settings);
        settings.c_oflag |= OPOST;
        settings.c_lflag |= ISIG;
        cfmakeraw(&settings);  //Set terminal to get raw input
        tcsetattr(0, TCSANOW, &settings);

        inputPoll = pollfd{0, POLLIN, 0};
    }

    RawConsoleInput::~RawConsoleInput() {
        tcsetattr(0, TCSANOW, &prevSettings); //Restore terminal settings
    }

    void RawConsoleInput::updateKeyStates() {
        clearKeys();
        while(poll(&inputPoll, 1, 0) && inputPoll.revents & POLLIN) {
            setKey(std::getchar(), true);
        }
    }
}
