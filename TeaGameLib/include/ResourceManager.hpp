#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectMsgQueue.hpp"
#include "InternalGameLib/Resource/ResourceLoader.hpp"

namespace teaGameLib {
	class ResourceManager {

		static InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		static void Init(InternalGameLibHandlersPtr _internalGameLibHandlersPtr) {
			ResourceManager::internalGameLibHandlersPtr = _internalGameLibHandlersPtr;
		}
		friend class App;
	public:

		template<typename Msg, typename MsgFunc>
		static Cmd<Msg> GetTextureResource(const std::string& fileName, MsgFunc msgFunc) {

			return { [fileName,msgFunc](EffectMsgQueue<Msg> effectMsgQueue) {
					auto result = resource::ResourceLoader::LoadTexture(
							fileName,
							internalGameLibHandlersPtr);
					
					effectMsgQueue.InQueueMsg(msgFunc(result));
			} };
		}

		template<typename Msg, typename MsgFunc>
		static Cmd<Msg> GetTextureResources(const std::vector<std::string>& fileNames, MsgFunc msgFunc) {

			return { [fileNames = std::move(fileNames),msgFunc] (EffectMsgQueue<Msg> effectMsgQueue) {
				std::vector<resource::TextureResource> textureResources;
				for (const auto& fileName : fileNames) {
					auto result = resource::ResourceLoader::LoadTexture(
						fileName,
						internalGameLibHandlersPtr);
					if (result.has_value() == false) {
						effectMsgQueue.InQueueMsg(msgFunc(std::optional<std::vector<resource::TextureResource>>{ }));
						return;
					}
					textureResources.emplace_back(result.value());
				}

				effectMsgQueue.InQueueMsg(msgFunc(std::optional{ std::move(textureResources) }));
			} };
		}

	};
}