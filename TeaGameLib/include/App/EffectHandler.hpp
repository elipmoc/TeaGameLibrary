#pragma once

#include "GameStates.hpp"
#include "EffectMsgQueue.hpp"
#include "EffectMsgQueueFactory/CreateCommonEffectMsgQueue.hpp"

namespace teaGameLib {

	class EffectHandler {
		bool isRunning = true;
		GameStates gameStates;

	public:
		EffectHandler(const GameStates& gameStates)
			:gameStates(gameStates) {}
		EffectHandler(const EffectHandler&) = delete;
		EffectHandler(EffectHandler&&) = default;
		EffectHandler& operator=(EffectHandler&&) = default;

		static EffectHandler&& SetEventStates(EffectHandler&& effectHandler, GameStates&& gameStates) {
			effectHandler.gameStates = gameStates;
			return std::move(effectHandler);
		}
		GameStates GetGameStates()const { return gameStates; }
		void EndGame() { isRunning = false; };
		bool GetIsRunning() const { return isRunning; }
	};
}