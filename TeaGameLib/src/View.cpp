#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"

namespace teaGameLib {
	void View::DrawSquare(const int x, const int y, const int length, const Color& color) {
		teaGameLib::DrawSquare(internalGameLibHandlersPtr, x, y, length, color);
	}
}