#include "raw-console-input.h"

namespace age {
    RawConsoleInput::RawConsoleInput() {
        std::unique_ptr<struct termios> settings = std::make_unique<struct termios>();
        prevSettings = std::make_unique<struct termios>();
        tcgetattr(0, prevSettings.get());
        tcgetattr(0, settings.get());
        settings->c_oflag |= OPOST;
        settings->c_lflag |= ISIG;
        cfmakeraw(settings.get());  //Set terminal to get raw input
        tcsetattr(0, TCSANOW, settings.get());

        inputPoll = std::make_unique<struct pollfd>(0, POLLIN, 0);
    }

    RawConsoleInput::~RawConsoleInput() {
        tcsetattr(0, TCSANOW, prevSettings.get()); //Restore terminal settings
    }

    void RawConsoleInput::updateKeyStates() {
        clearKeys();
        while(poll(inputPoll.get(), 1, 0) && inputPoll->revents & POLLIN) {
            setKey(std::getchar(), true);
        }
    }
}
