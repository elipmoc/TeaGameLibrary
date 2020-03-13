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
		DrawSprite(sdlHandlers, textureResource, centerPos, 0);
	}
	void DrawSprite(
		InternalGameLibHandlersPtr& sdlHandlers, const resource::TextureResource& textureResource,
		const math::Vector2D<int>& centerPos, double angle)
	{
		DrawSprite(sdlHandlers, textureResource, centerPos, { 1.0f,1.0f }, angle);
	}
	void DrawSprite(
		InternalGameLibHandlersPtr& sdlHandlers, const resource::TextureResource& textureResource,
		const math::Vector2D<int>& centerPos, const math::Vector2D<float>& scale, double angle)
	{
		if (textureResource.GetImpl()->ptr == nullptr)return;

		const float width = textureResource.GetWidth() * scale.x;
		const float height = textureResource.GetHeight() * scale.y;

		SDL_Rect r{
			centerPos.x - static_cast<int>(width / 2),
			centerPos.y - static_cast<int>(height / 2),
			static_cast<int>(width),
			static_cast<int>(height)
		};
		SDL_RenderCopyEx(sdlHandlers->sdlRendererPtr,
			textureResource.GetImpl()->ptr,
			nullptr,
			&r,
			angle,
			nullptr,
			SDL_FLIP_NONE);
	}
}