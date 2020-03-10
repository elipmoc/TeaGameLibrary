#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"

namespace teaGameLib {
	void View::DrawSquare(const math::Vector2D<int>& v, const int length, const Color& color) {
		teaGameLib::DrawSquare(internalGameLibHandlersPtr, v, length, color);
	}
	void View::DrawRect(const math::Vector2D<int>& leftUpPos, const math::Vector2D<int>& size, const Color& color)
	{
		teaGameLib::DrawRect(internalGameLibHandlersPtr, leftUpPos, size, color);
	}
}