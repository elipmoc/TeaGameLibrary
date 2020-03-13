#include "../Interface/DrawSprite.hpp"
#include "Resource/SDLTextureResourceImpl.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {
	void DrawSprite(
		InternalGameLibHandlersPtr& sdlHandlers,
		const resource::TextureResource& textureResource,
		const math::Vector2D<int>& centerPos)
	{
		SDL_Rect r{
			centerPos.x - textureResource.GetWidth() / 2,
			centerPos.y - textureResource.GetHeight() / 2,
			textureResource.GetWidth(),
			textureResource.GetHeight()
		};
		SDL_RenderCopyEx(sdlHandlers->sdlRendererPtr,
			textureResource.GetImpl()->ptr,
			nullptr,
			&r,
			0,
			nullptr,
			SDL_FLIP_NONE);
	}
}