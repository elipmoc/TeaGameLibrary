#pragma once
#include "GameStates.hpp"
#include "InternalGameLib/InternalGameLib.hpp"

namespace teaGameLib {
	GameStates ProcessInput() {
		return GameStates{
			GetEventStates(),
			GetKeyStates()
		};
	}
}