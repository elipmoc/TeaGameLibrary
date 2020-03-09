#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"

namespace teaGameLib {
	void View::DrawSquare(const math::Vector2D<int>& v, const int length, const Color& color) {
		teaGameLib::DrawSquare(internalGameLibHandlersPtr, v, length, color);
	}
}