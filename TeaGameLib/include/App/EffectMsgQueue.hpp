#pragma once
#include <queue>
#include <optional>

namespace teaGameLib {
    template<typename Msg>
    class EffectMsgQueue {
        using InQueueFunc = std::function<void(const Msg&)>;

        InQueueFunc inQueueFunc;

    public:

        EffectMsgQueue(InQueueFunc inQueueFunc)
            :inQueueFunc(inQueueFunc) {}

        void InQueueMsg(const Msg& msg) { inQueueFunc(msg); }

        template<typename NewMsg>
        using MapFunc = std::function<Msg(NewMsg)>;

        template<typename NewMsg>
        EffectMsgQueue<NewMsg> Map(MapFunc<NewMsg> mapFunc) {
            return  EffectMsgQueue<NewMsg>{
                [=](const NewMsg& newMsg) {
                    return  inQueueFunc(mapFunc(newMsg));
                }
            };
        }
    };
}