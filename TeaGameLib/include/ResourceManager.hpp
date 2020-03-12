#pragma once

#include "Platform/Effect.hpp"
#include "Window/App/EffectParams.hpp"
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
		static Cmd<Msg> GetTexturePtr(const std::string& fileName, MsgFunc msgFunc) {

			return { [fileName,msgFunc](EffectParams<Msg> effectParams) {
					auto result = resource::ResourceLoader::LoadTexture(
							fileName,
							internalGameLibHandlersPtr);
					
					effectParams.effectMsgQueue.InQueueMsg(msgFunc(result));
			} };
		}
	};
}