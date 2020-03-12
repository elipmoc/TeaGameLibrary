#pragma once

#include "Window/App/WindowData.hpp"
#include "InternalGameLib/InternalGameLibHandlers.hpp"
#include <optional>

namespace teaGameLib {

	class GameInitializer {
	public:
		static std::optional<InternalGameLibHandlersPtr>Init(const WindowData&);
	};
}