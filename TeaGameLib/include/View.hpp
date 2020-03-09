#pragma once

#include "InternalGameLib/InternalGameLibHandlers.hpp"
#include "Color.hpp"
#include "Math/Vector2D.hpp"

namespace teaGameLib {
	struct View {
		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View(InternalGameLibHandlersPtr& internalGameLibHandlersPtr) :internalGameLibHandlersPtr(internalGameLibHandlersPtr) {}
		void DrawSquare(const math::Vector2D<int>&, const int length, const Color&);
	};
}