#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"
#include "Window/App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	struct Input {
		template<typename Msg>
		static Sub<Msg> KeyInput(KeyCode keyCode, Msg msg) {
			return { [keyCode,msg](EffectParams<Msg> effectParams) {
					if (effectParams.effectHandler.GetGameStates().keyStates.GetKeyInput(keyCode))
						effectParams.effectMsgQueue.InQueueMsg(msg);
			} };
		}
	};
}