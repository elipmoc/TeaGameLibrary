#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectMsgQueue.hpp"

namespace teaGameLib {
	class WindowEvent {
		static windowEvent::EventStates eventStates;
		
		static void Init(const windowEvent::EventStates& _eventStates) {
			eventStates = _eventStates;
		}
		friend class App;

	public:

		template<typename Msg>
		static Sub<Msg> Quit(Msg msg) {
			return{
				[msg](EffectMsgQueue<Msg> effectMsgQueue) {
					if (eventStates.isQuit)
						effectMsgQueue.InQueueMsg(msg);
				}
			};
		}
	};
}