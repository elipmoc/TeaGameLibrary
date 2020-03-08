#pragma once
#include <queue>
#include <optional>
#include "../EffectMsgQueue.hpp" 

namespace teaGameLib {

    template<typename Msg>
    EffectMsgQueue<Msg> CreateCommonEffectMsgQueue(std::queue<Msg>& queue) {
        return EffectMsgQueue<Msg>{
            [&queue](const Msg& msg) {
                queue.push(msg);
            }
        };
    }
}