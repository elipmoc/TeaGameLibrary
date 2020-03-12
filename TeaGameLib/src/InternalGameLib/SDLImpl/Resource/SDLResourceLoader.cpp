#pragma once
#include "InternalGameLib/Resource/ResourceLoader.hpp"
#include "SDLTextureResourceImpl.hpp"
#include "InternalGameLib/Resource/TextureResource.hpp"
#include "../SDLHandlers.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

namespace teaGameLib::resource {
	std::optional<TextureResource> ResourceLoader::LoadTexture(
		const std::string& fileName,
		InternalGameLibHandlersPtr sdlHandlers
	) {
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return std::nullopt;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlHandlers->sdlRendererPtr, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return std::nullopt;
		}
		int width;
		int height;
		SDL_QueryTexture(tex, nullptr, nullptr, &width, &height);
		return { { std::make_shared<TextureResource::TextureResourceImpl>(tex,width,height) } };
	}
}