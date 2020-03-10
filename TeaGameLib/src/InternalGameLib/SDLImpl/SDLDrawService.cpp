#include "InternalGameLib/DrawService.hpp"
#include "SDL/SDL.h"
#include "SDLHandlers.hpp"

namespace teaGameLib {

	void DrawService::RenderPresent(InternalGameLibHandlersPtr& sdlHandlers)
	{
		SDL_RenderPresent(sdlHandlers->sdlRendererPtr);
	}
	void DrawService::RenderClear(InternalGameLibHandlersPtr& sdlHandlers,const Color& color)
	{
		auto const [r, g, b, a] = color;
		SDL_SetRenderDrawColor(
			sdlHandlers->sdlRendererPtr,
			r, g, b, a
		);

		SDL_RenderClear(sdlHandlers->sdlRendererPtr);
	}
}
