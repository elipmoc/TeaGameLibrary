#pragma once
#include "../Input/KeyStates.hpp"
#include "../Window/App/GameStates/EventStates.hpp"

namespace teaGameLib {
	input::KeyStates GetKeyStates();
	EventStates GetEventStates();
}