#pragma once
#include <cstdint>

namespace teaGameLib {
    class Color {
    public:
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a = 255;
        static constexpr Color Black() { return { 0,0,0 }; };
        static constexpr Color White() { return { 255,255,255 }; };
        static constexpr Color Red() { return { 255,0,0 }; };
        static constexpr Color Green() { return { 0,255,0 }; };
        static constexpr Color Blue() { return { 0,0,255 }; };
    };

 }