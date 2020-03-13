#pragma once

#include "../Color.hpp"

namespace teaGameLib::gameWorld {

	class GameWorldData {
		bool isRunning = true;
		Color backgroundColor = Color::Black();

	public:
		GameWorldData() {}
		GameWorldData(const GameWorldData&) = delete;
		GameWorldData(GameWorldData&&) = default;
		GameWorldData& operator=(GameWorldData&&) = default;

		void EndGame() { isRunning = false; };
		void SetBackGroundColor(const Color& color) { backgroundColor = color; }
		Color GetBackGroundColor() { return backgroundColor; }
		bool GetIsRunning() const { return isRunning; }
	};
}