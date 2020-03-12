#include "Window/App.hpp"
#include "View.hpp"
#include "GameWorld.hpp"
#include "ResourceManager.hpp"
#include "../InternalGameLib/Interface/GameInitializer.hpp"

namespace teaGameLib {
	
	InternalGameLibHandlersPtr ResourceManager::internalGameLibHandlersPtr;
	EffectHandler* GameWorld::effectHandler;
	KeyStates Input::keyStates;
	EventStates WindowEvent::eventStates;

	App::App(InternalGameLibHandlersPtr internalGameLibHandlersPtr)
		:internalGameLibHandlersPtr(internalGameLibHandlersPtr), view({ internalGameLibHandlersPtr }) {
		ResourceManager::Init(internalGameLibHandlersPtr);
		GameWorld::Init(effectHandler);

	}

	App App::CreateApp(WindowData windowData) {
		std::optional<InternalGameLibHandlersPtr> internalGameLibHandlers = GameInitializer::Init(windowData);
		if (internalGameLibHandlers.has_value() == false) {
			throw "";
		}
		return App{ internalGameLibHandlers.value() };
	}
}