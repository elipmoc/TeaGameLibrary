#pragma once
#include "GameStates/KeyStates.hpp"
#include "GameStates/EventStates.hpp"

namespace teaGameLib {
	struct GameStates {
		EventStates eventStates;
		KeyStates keyStates={};
	};
}