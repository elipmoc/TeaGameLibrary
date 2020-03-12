#pragma once
#include "GameStates.hpp"
#include "../../InternalGameLib/InternalGameLib.hpp"

namespace teaGameLib {
	inline GameStates ProcessInput() {
		return GameStates{
			GetEventStates(),
			GetKeyStates()
		};
	}
}