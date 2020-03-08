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
        static Cmd<Msg> EndGame() {
            return Cmd<Msg>(EndGameCmd<Msg>{});
        }
    };
}