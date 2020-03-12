#pragma once
#include "InternalGameLib/InternalGameLibHandlers.hpp"

namespace teaGameLib {

	class GameShutDown {
	public:
		static void ShutDown(InternalGameLibHandlersPtr);
	};
}