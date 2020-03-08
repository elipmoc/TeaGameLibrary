#pragma once
#include "InternalGameLibHandlers.hpp"

namespace teaGameLib {

	class GameShutDown {
	public:
		static void ShutDown(InternalGameLibHandlersPtr);
	};
}