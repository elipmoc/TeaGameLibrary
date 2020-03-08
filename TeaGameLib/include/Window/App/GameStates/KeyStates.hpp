#pragma once
#include <cstdint>
#include "KeyCode.hpp"

namespace teaGameLib {

    class KeyStates {
        const std::uint8_t* state;
    public:
        KeyStates(const std::uint8_t* state) :state(state) {}
        KeyStates():state(nullptr) {}
        bool GetKeyInput(const KeyCode keycode)const {
            return state[static_cast<unsigned int>(keycode)];
        }
    };
}