#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"

namespace teaGameLib {
	void View::DrawBall(const int x, const int y, const int thickness) {
		teaGameLib::DrawBall(internalGameLibHandlersPtr, x, y, thickness);
	}
}