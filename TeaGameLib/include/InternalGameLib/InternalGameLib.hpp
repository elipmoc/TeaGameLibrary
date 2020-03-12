#pragma once
#include "../Input/KeyStates.hpp"
#include "../WindowEvent/EventStates.hpp"

namespace teaGameLib {
	input::KeyStates GetKeyStates();
	windowEvent::EventStates GetEventStates();
}