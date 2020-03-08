#pragma once
#include <memory>
#include "App/Effect.hpp"
#include "CmdImpls/EndGameCmd.hpp"
#include "CmdImpls/IdCmd.hpp"

#include "SubImpls/QuitEventSub.hpp" 
#include "SubImpls/KeyInputEventSub.hpp" 

namespace teaGameLib {
    class CmdBuilder {
    public:

        template<typename Msg>
        static Cmd<Msg> Id(Msg msg) {
            return Cmd<Msg>(IdCmd<Msg>{msg});
        }

        template<typename Msg>
        static Cmd<Msg> EndGame() {
            return Cmd<Msg>(EndGameCmd<Msg>{});
        }

        template<typename Msg>
        static Cmd<Msg> QuitEvent(Msg msg) {
            return Cmd<Msg>(QuitEventSub<Msg>{msg});
        }

        template<typename Msg>
        static Cmd<Msg> KeyInputEvent(const KeyCode keyCode, Msg msg) {
            return Cmd<Msg>(KeyInputEventSub<Msg>{keyCode, msg});
        }
    };
}