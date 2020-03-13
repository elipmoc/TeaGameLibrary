#pragma once
#include "InternalGameLib/Resource/TextureResource.hpp"
#include "SDLTextureResourceImpl.hpp"

namespace teaGameLib::resource {
	TextureResource::TextureResource(std::shared_ptr<TextureResource::TextureResourceImpl> impl) :impl(impl) {}
	TextureResource::TextureResource() : impl(std::make_shared<TextureResource::TextureResourceImpl>( nullptr,0,0 )) {}
	
	TextureResource::~TextureResource() = default;

	int TextureResource::GetWidth() const
	{
		return impl->width;
	}

	int TextureResource::GetHeight() const
	{
		return impl->height;
	}

	std::shared_ptr<TextureResource::TextureResourceImpl> TextureResource::GetImpl()const noexcept {
		return impl;
	}
}