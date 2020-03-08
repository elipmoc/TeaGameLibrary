#include "InternalGameLib/GameShutDown.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	void GameShutDown::ShutDown(InternalGameLibHandlersPtr sdlHandlers)
	{
		SDL_DestroyRenderer(sdlHandlers->sdlRendererPtr);
		SDL_DestroyWindow(sdlHandlers->sdlWindowPtr);
		SDL_Quit();
		delete sdlHandlers;
	}
}
