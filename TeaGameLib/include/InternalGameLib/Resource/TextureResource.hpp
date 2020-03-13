#pragma once
#include <memory>


namespace teaGameLib::resource {
	class TextureResource {
	public:
		struct TextureResourceImpl;
	private:
		std::shared_ptr<TextureResourceImpl> impl;
	public:
		TextureResource(std::shared_ptr<TextureResourceImpl> impl);
		TextureResource();
		~TextureResource();

		int GetWidth()const;
		int GetHeight()const;

		std::shared_ptr<TextureResourceImpl> GetImpl() const noexcept;
	};
}