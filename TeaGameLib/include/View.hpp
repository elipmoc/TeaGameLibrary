#pragma once

#include "InternalGameLib/InternalGameLibHandlers.hpp"
#include "Color.hpp"
#include "Math/Vector2D.hpp"

namespace teaGameLib {
	struct View {
		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View(InternalGameLibHandlersPtr& internalGameLibHandlersPtr) :internalGameLibHandlersPtr(internalGameLibHandlersPtr) {}
		void DrawSquare(const math::Vector2D<int>& centerPos, const int length, const Color&);
		void DrawRect(const math::Vector2D<int>& leftUpPos, const math::Vector2D<int>& size, const Color&);
	};
}