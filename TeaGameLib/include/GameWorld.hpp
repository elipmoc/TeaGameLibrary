#pragma once

#include "App/Effect.hpp"
#include "App/EffectParams.hpp"
#include "App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	struct GameWorld {
		template<typename Msg>
		static Cmd<Msg> EndGame() {
			return { [](EffectParams<Msg> effectParams) {
				effectParams.effectHandler.EndGame();
			} };
		}
	};
}