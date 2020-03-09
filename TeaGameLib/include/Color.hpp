#pragma once

namespace teaGameLib {
    class Color {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;
        unsigned int a = 255;
        static constexpr Color Black() { return { 0,0,0 }; };
        static constexpr Color White() { return { 255,255,255 }; };
        static constexpr Color Red() { return { 255,0,0 }; };
        static constexpr Color Green() { return { 0,255,0 }; };
        static constexpr Color Blue() { return { 0,0,255 }; };
    };

 }