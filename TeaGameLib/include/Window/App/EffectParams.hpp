#pragma once

#include "EffectHandler.hpp"
#include "EffectMsgQueue.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct EffectParams {
		EffectMsgQueue<Msg> effectMsgQueue;	
	};
}