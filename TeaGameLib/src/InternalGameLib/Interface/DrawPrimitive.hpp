#pragma once
#include "../include/InternalGameLib/InternalGameLibHandlers.hpp"
#include "Color.hpp"
#include "Math/Vector2D.hpp"

namespace teaGameLib {
	void DrawSquare(InternalGameLibHandlersPtr&, const math::Vector2D<int>&, const int length, const Color&);
	void DrawRect(InternalGameLibHandlersPtr&, const math::Vector2D<int>& leftUpPos, const math::Vector2D<int>& size, const Color&);
}