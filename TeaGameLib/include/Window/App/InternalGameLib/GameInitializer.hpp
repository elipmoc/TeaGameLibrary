#pragma once

#include "../InitData.hpp"
#include "InternalGameLibHandlers.hpp"
#include <optional>

namespace teaGameLib {

	class GameInitializer {
	public:
		static std::optional<InternalGameLibHandlersPtr>Init(const WindowData&);
	};
}