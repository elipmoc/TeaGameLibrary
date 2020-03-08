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
		const WindowData windowData;
		InitData(Model&& model, WindowData windowData) :model(std::move(model)), windowData(windowData) {};
		InitData(const InitData& initData) :model(std::move(initData.model)), windowData(initData.windowData) {};
		InitData(InitData&&) = delete;
	};
}
