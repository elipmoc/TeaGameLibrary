#pragma once
#include "../../Input/KeyStates.hpp"
#include "GameStates/EventStates.hpp"

namespace teaGameLib {
	struct GameStates {
		EventStates eventStates;
		input::KeyStates keyStates={};
	};
}