#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"
#include "Window/App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	class Input {
		static KeyStates keyStates;
		
		static void Init(const KeyStates& _keyStates) {
			keyStates = _keyStates;
		}

		friend class App;

	public:

		template<typename Msg>
		static Sub<Msg> KeyInput(KeyCode keyCode, Msg msg) {
			return { [keyCode,msg](EffectParams<Msg> effectParams) {
					if (keyStates.GetKeyInput(keyCode))
						effectParams.effectMsgQueue.InQueueMsg(msg);
			} };
		}
	};
}