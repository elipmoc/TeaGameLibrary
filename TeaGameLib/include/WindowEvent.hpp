#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"

namespace teaGameLib {
	class WindowEvent {
		static EventStates eventStates;
	public:
		static void Init(const EventStates& _eventStates) {
			eventStates = _eventStates;
		}

		template<typename Msg>
		static Sub<Msg> Quit(Msg msg) {
			return{
				[msg](EffectParams<Msg> effectParams) {
					if (eventStates.isQuit)
						effectParams.effectMsgQueue.InQueueMsg(msg);
				}
			};
		}
	};
}