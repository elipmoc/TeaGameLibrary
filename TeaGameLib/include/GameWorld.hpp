#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectMsgQueue.hpp"
#include "GameWorld/GameWorldData.hpp"

namespace teaGameLib {
	class GameWorld {

		static gameWorld::GameWorldData* gameWorldData;

		static void Init(gameWorld::GameWorldData& _gameWorldData) { gameWorldData = &_gameWorldData; }

		friend class App;
	public:
		template<typename Msg>
		static Cmd<Msg> EndGame() {
			return { [](EffectMsgQueue<Msg>) {
				gameWorldData->EndGame();
			} };
		}

		template<typename Msg>
		static Cmd<Msg> SetBackGroundColor(const Color& color) {
			return { [color](EffectMsgQueue<Msg>) {
				gameWorldData->SetBackGroundColor(color);
			} };
		}
	};
}