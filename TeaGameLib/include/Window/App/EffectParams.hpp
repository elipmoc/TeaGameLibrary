#pragma once

#include "EffectHandler.hpp"
#include "EffectMsgQueue.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct EffectParams {
		EffectHandler& effectHandler;
		EffectMsgQueue<Msg> effectMsgQueue;	
	};
}