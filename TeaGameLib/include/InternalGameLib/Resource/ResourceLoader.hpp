#pragma once
#include "TextureResource.hpp"
#include "../InternalGameLibHandlers.hpp"
#include <optional>
#include <string>

namespace teaGameLib::resource {
	class ResourceLoader {
	public:
		static std::optional<TextureResource> LoadTexture(const std::string& fileName, InternalGameLibHandlersPtr internalGameLibHandlersPtr);
	};
}