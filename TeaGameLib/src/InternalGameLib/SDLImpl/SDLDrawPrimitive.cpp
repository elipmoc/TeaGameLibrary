#include "../Interface/DrawPrimitive.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	void DrawSquare(InternalGameLibHandlersPtr& sdlHandlers, const math::Vector2D<int>& v, const int length, const Color& color)
	{
		const auto [r, g, b, a] = color;
		const auto [x, y] = v - math::Vector2D<int>{length / 2, length / 2};
		SDL_SetRenderDrawColor(sdlHandlers->sdlRendererPtr, r, g, b, a);
		SDL_Rect ball{ x ,y ,length,length };
		SDL_RenderFillRect(sdlHandlers->sdlRendererPtr, &ball);
	}
}