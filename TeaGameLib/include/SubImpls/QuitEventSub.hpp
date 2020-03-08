#pragma once
#include "../App/Effect.hpp"
#include "../App/EffectParams.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct QuitEventSub {
		const Msg msg;
		QuitEventSub(Msg msg) :msg(msg) {}
		void operator()(EffectParams<Msg> effectParams) {
			if (effectParams.effectHandler.GetGameStates().eventStates.isQuit)
				effectParams.effectMsgQueue.InQueueMsg(msg);
		};
	};
}