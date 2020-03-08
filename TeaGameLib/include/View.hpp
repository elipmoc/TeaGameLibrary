#pragma once

#include "InternalGameLib/InternalGameLibHandlers.hpp"

namespace teaGameLib {
	struct View {
		static void DrawBall(InternalGameLibHandlersPtr&, const int x, const int y, const int thickness);
	};
}