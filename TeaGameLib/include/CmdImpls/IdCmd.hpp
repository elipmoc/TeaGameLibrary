#pragma once
#include "../App/Effect.hpp"
#include "../App/EffectParams.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct IdCmd {
		const Msg msg;
		IdCmd(Msg msg) :msg(msg) {}
		void operator()(EffectParams<Msg>& effectParams) {
			effectParams.effectMsgQueue.InQueueMsg(msg);
		};
	};
}