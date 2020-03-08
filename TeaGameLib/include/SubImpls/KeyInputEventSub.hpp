#pragma once

#pragma once
#include "../App/Effect.hpp"
#include "../App/EffectParams.hpp"
#include "../App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct KeyInputEventSub {
		const Msg msg;
		const KeyCode keyCode;
		KeyInputEventSub(KeyCode keyCode, Msg msg) :msg(msg), keyCode(keyCode) {}
		void operator()(EffectParams<Msg> effectParams) {
			if (effectParams.effectHandler.GetGameStates().keyStates.GetKeyInput(keyCode))
				effectParams.effectMsgQueue.InQueueMsg(msg);
		};
	};
}