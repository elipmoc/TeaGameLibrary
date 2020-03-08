#include "../Interface/DrawPrimitive.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	void DrawBall(InternalGameLibHandlersPtr& sdlHandlers, const int x, const int y, const int thickness)
	{
		SDL_SetRenderDrawColor(sdlHandlers->sdlRendererPtr, 0, 255, 255, 255);
		SDL_Rect ball{
			x - thickness / 2,
			y - thickness / 2,
			thickness,
			thickness
		};
		SDL_RenderFillRect(sdlHandlers->sdlRendererPtr, &ball);
	}
}