#pragma once
#include "InternalGameLib/Resource/TextureResource.hpp"
#include "SDL/SDL.h"

namespace teaGameLib::resource {

	struct TextureResource::TextureResourceImpl {
		SDL_Texture* ptr;
		const int width;
		const int height;
		TextureResourceImpl(SDL_Texture* ptr,int width,int height) :ptr(ptr),width(width),height(height) {}
		~TextureResourceImpl() { SDL_DestroyTexture(ptr); }
	};

}
