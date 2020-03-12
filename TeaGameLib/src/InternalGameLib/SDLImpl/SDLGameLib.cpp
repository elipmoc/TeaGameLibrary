#include "InternalGameLib/InternalGameLib.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {
	input::KeyStates GetKeyStates() {
		return input::KeyStates{ SDL_GetKeyboardState(NULL) };
	}

	EventStates GetEventStates() {
		SDL_Event event;
		bool isQuit = false;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isQuit = true;
				break;
			}
		}
		return EventStates{ isQuit };
	}
}