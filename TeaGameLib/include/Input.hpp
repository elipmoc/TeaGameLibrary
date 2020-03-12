#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectMsgQueue.hpp"
#include "Input/KeyStates.hpp"

namespace teaGameLib {
	class Input {
		static input::KeyStates keyStates;

		static void Init(const input::KeyStates& _keyStates) {
			keyStates = _keyStates;
		}

		friend class App;

	public:

		template<typename Msg>
		static Sub<Msg> KeyInput(input::KeyCode keyCode, Msg msg) {
			return { [keyCode,msg](EffectMsgQueue<Msg> effectMsgQueue) {
					if (keyStates.GetKeyInput(keyCode))
						effectMsgQueue.InQueueMsg(msg);
			} };
		}
	};
}