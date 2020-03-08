#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"

namespace teaGameLib {
	struct WindowEvent {
		template<typename Msg>
		static Sub<Msg> Quit(Msg msg) {
			return{
				[msg](EffectParams<Msg> effectParams) {
					if (effectParams.effectHandler.GetGameStates().eventStates.isQuit)
						effectParams.effectMsgQueue.InQueueMsg(msg);
				}
			};
		}
	};
}