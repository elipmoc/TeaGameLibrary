#include "../Interface/DrawPrimitive.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	void DrawSquare(InternalGameLibHandlersPtr& sdlHandlers, const int x, const int y, const int length, const Color& color)
	{
		const auto [r, g, b, a] = color;
		SDL_SetRenderDrawColor(sdlHandlers->sdlRendererPtr, r, g, b, a);
		SDL_Rect ball{
			x - length / 2,
			y - length / 2,
			length,
			length
		};
		SDL_RenderFillRect(sdlHandlers->sdlRendererPtr, &ball);
	}
}