#pragma once

#include "InternalGameLib/InternalGameLibHandlers.hpp"

namespace teaGameLib {
	struct View {
		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View(InternalGameLibHandlersPtr& internalGameLibHandlersPtr) :internalGameLibHandlersPtr(internalGameLibHandlersPtr) {}
		void DrawBall(const int x, const int y, const int thickness);
	};
}