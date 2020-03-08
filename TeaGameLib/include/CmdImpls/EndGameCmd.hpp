#pragma once
#include "../App/Effect.hpp"
#include "../App/EffectParams.hpp"

namespace teaGameLib {
	template<typename Msg>
	struct EndGameCmd {
		void operator()(EffectParams<Msg> effectParams) {
			effectParams.effectHandler.EndGame();
		};
	};
}