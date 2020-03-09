#pragma once
#include "../include/InternalGameLib/InternalGameLibHandlers.hpp"
#include "Color.hpp"

namespace teaGameLib {
	void DrawSquare(InternalGameLibHandlersPtr&, const int x, const int y, const int length, const Color&);
}