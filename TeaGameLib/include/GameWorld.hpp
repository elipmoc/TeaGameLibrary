#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"
#include "Window/App/GameStates/KeyStates.hpp"

namespace teaGameLib {
	class GameWorld {

		static EffectHandler* effectHandler;

		static void Init(EffectHandler& _effectHandler) { effectHandler = &_effectHandler; }

		friend class App;
	public:
		template<typename Msg>
		static Cmd<Msg> EndGame() {
			return { [](EffectParams<Msg>) {
				effectHandler->EndGame();
			} };
		}

		template<typename Msg>
		static Cmd<Msg> SetBackGroundColor(const Color& color) {
			return { [color](EffectParams<Msg>) {
				effectHandler->SetBackGroundColor(color);
			} };
		}
	};
}