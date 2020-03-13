#pragma once
#include <vector>
#include "../InternalGameLib/Resource/TextureResource.hpp"

namespace teaGameLib::utilModel {

	//単一のスプライトアニメーション処理を行うモデル
	class AnimSpriteModel {
		float currentFrame = 0;
		std::vector<resource::TextureResource> textureResources;
	public:
		float fps;
		AnimSpriteModel(std::vector<resource::TextureResource>&& textureResources, float fps) :fps(fps), textureResources(std::move(textureResources)) {}
		AnimSpriteModel(AnimSpriteModel&&) = default;
		AnimSpriteModel& operator=(AnimSpriteModel&&) =default;
		AnimSpriteModel(const AnimSpriteModel&) = delete;
		AnimSpriteModel& operator=(const AnimSpriteModel&) = delete;

		void Update(float deltaTime) {
			currentFrame += fps * deltaTime;
		}

		resource::TextureResource GetCurrentTextureResource()const {
			return
				textureResources.size() == 0 ?
				resource::TextureResource{} :
				textureResources[static_cast<int>(currentFrame) % textureResources.size()];
		}
	};
}