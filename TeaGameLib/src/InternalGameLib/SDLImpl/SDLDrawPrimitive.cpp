#include "../Interface/DrawPrimitive.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	void DrawSquare(InternalGameLibHandlersPtr& sdlHandlers, const math::Vector2D<int>& pos, const int length, const Color& color)
	{
		const auto size = math::Vector2D<int>{ length, length };
		const auto leftUpPos = pos - size / 2;
		DrawRect(sdlHandlers, pos, size, color);
	}
	void  DrawRect(InternalGameLibHandlersPtr& sdlHandlers, const math::Vector2D<int>& leftUpPos, const math::Vector2D<int>& size, const Color& color)
	{
		const auto [r, g, b, a] = color;
		const auto [x, y] = leftUpPos;
		const auto [width, height] = size;
		SDL_SetRenderDrawColor(sdlHandlers->sdlRendererPtr, r, g, b, a);
		SDL_Rect ball{ x ,y ,width,height };
		SDL_RenderFillRect(sdlHandlers->sdlRendererPtr, &ball);
	}
}