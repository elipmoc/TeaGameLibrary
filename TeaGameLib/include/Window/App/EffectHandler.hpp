#pragma once

#include "GameStates.hpp"
#include "../../Color.hpp"
#include "EffectMsgQueue.hpp"
#include "EffectMsgQueueFactory/CreateCommonEffectMsgQueue.hpp"

namespace teaGameLib {

	class EffectHandler {
		bool isRunning = true;
		Color backgroundColor = Color::Black();
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
		void SetBackGroundColor(const Color& color) { backgroundColor = color; }
		Color GetBackGroundColor() { return backgroundColor; }
		bool GetIsRunning() const { return isRunning; }
	};
}