#pragma once
#include "../../Input/KeyStates.hpp"
#include "../../WindowEvent/EventStates.hpp"

namespace teaGameLib {
	struct GameStates {
		windowEvent::EventStates eventStates;
		input::KeyStates keyStates={};
	};
}