#pragma once

#include "GameStates.hpp"
#include "../../Color.hpp"
#include "EffectMsgQueue.hpp"
#include "EffectMsgQueueFactory/CreateCommonEffectMsgQueue.hpp"

namespace teaGameLib {

	class EffectHandler {
		bool isRunning = true;
		Color backgroundColor = Color::Black();

	public:
		EffectHandler() {}
		EffectHandler(const EffectHandler&) = delete;
		EffectHandler(EffectHandler&&) = default;
		EffectHandler& operator=(EffectHandler&&) = default;

		void EndGame() { isRunning = false; };
		void SetBackGroundColor(const Color& color) { backgroundColor = color; }
		Color GetBackGroundColor() { return backgroundColor; }
		bool GetIsRunning() const { return isRunning; }
	};
}