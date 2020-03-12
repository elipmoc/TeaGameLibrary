#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectMsgQueue.hpp"
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
			return { [keyCode,msg](EffectMsgQueue<Msg> effectMsgQueue) {
					if (keyStates.GetKeyInput(keyCode))
						effectMsgQueue.InQueueMsg(msg);
			} };
		}
	};
}