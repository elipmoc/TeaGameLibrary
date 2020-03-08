#pragma once

#include "App/Effect.hpp"
#include "App/EffectParams.hpp"
#include "App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	struct Input {
		template<typename Msg>
		static Sub<Msg> KeyInput(KeyCode keyCode, Msg msg) {
			return { [](EffectParams<Msg> effectParams) {
					if (effectParams.effectHandler.GetGameStates().keyStates.GetKeyInput(keyCode))
						effectParams.effectMsgQueue.InQueueMsg(msg);
			} };
		}
	};
}