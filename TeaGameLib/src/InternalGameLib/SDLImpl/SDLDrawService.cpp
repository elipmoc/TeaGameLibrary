#include "App/InternalGameLib/DrawService.hpp"
#include "SDL/SDL.h"
#include "SDLHandlers.hpp"

namespace teaGameLib {

	void DrawService::RenderPresent(InternalGameLibHandlersPtr& sdlHandlers)
	{
		SDL_RenderPresent(sdlHandlers->sdlRendererPtr);
	}
	void DrawService::RenderClear(InternalGameLibHandlersPtr& sdlHandlers)
	{
		SDL_SetRenderDrawColor(
			sdlHandlers->sdlRendererPtr,
			0,		// R
			0,		// G 
			0,	    // B
			255		// A
		);

		SDL_RenderClear(sdlHandlers->sdlRendererPtr);
	}
}
