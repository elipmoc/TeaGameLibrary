#pragma once
#include "InternalGameLibHandlers.hpp"
#include "../Color.hpp"

namespace teaGameLib {

	class DrawService {
		static void RenderPresent(InternalGameLibHandlersPtr&);
		static void RenderClear(InternalGameLibHandlersPtr&, const Color& color);
	public:
		template<typename ViewFunc>
		static void Draw(InternalGameLibHandlersPtr& internalGameLibHandlers, const Color& color, ViewFunc viewFunc) {
			RenderClear(internalGameLibHandlers, color);
			viewFunc();
			RenderPresent(internalGameLibHandlers);
		}
	};
}