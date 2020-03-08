#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"
#include "Window/App/GameStates/KeyStates.hpp"

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