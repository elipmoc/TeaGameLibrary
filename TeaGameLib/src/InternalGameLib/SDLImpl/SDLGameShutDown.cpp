#include "InternalGameLib/GameShutDown.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

namespace teaGameLib {

	void GameShutDown::ShutDown(InternalGameLibHandlersPtr sdlHandlers)
	{
		IMG_Quit();
		SDL_DestroyRenderer(sdlHandlers->sdlRendererPtr);
		SDL_DestroyWindow(sdlHandlers->sdlWindowPtr);
		SDL_Quit();
		delete sdlHandlers;
	}
}
