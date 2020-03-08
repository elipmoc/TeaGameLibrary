#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"

namespace teaGameLib {
	void View::DrawBall(InternalGameLibHandlersPtr& internalGameLibHandlersPtr, const int x, const int y, const int thickness) {
		teaGameLib::DrawBall(internalGameLibHandlersPtr, x, y, thickness);
	}
}