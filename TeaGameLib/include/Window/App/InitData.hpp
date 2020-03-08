#pragma once
#include <string>

namespace teaGameLib {

	struct WindowData
	{
		const std::string title;
		const int topLeftX;
		const int topLeftY;
		const int width;
		const int height;
	};

	template<typename Model>
	struct InitData {
		Model model;
		InitData(Model&& model) :model(std::move(model)) {};
		InitData(const InitData& initData) :model(std::move(initData.model)) {};
		InitData(InitData&&) = delete;
	};
}
