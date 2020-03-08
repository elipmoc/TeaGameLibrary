#pragma once
#include "InternalGameLibHandlers.hpp"

namespace teaGameLib {

	class DrawService {
		static void RenderPresent(InternalGameLibHandlersPtr&);
		static void RenderClear(InternalGameLibHandlersPtr&);
	public:
		template<typename ViewFunc>
		static void Draw(InternalGameLibHandlersPtr& internalGameLibHandlers, ViewFunc viewFunc) {
			RenderClear(internalGameLibHandlers);
			viewFunc(internalGameLibHandlers);
			RenderPresent(internalGameLibHandlers);
		}
	};
}