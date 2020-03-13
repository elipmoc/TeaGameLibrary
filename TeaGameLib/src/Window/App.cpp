#include "Window/App.hpp"
#include "View.hpp"
#include "GameWorld.hpp"
#include "Input.hpp"
#include "WindowEvent.hpp"
#include "ResourceManager.hpp"
#include "../InternalGameLib/Interface/GameShutDown.hpp"
#include "../InternalGameLib/Interface/GameInitializer.hpp"

namespace teaGameLib {
	
	InternalGameLibHandlersPtr ResourceManager::internalGameLibHandlersPtr;
	gameWorld::GameWorldData* GameWorld::gameWorldData;
	input::KeyStates Input::keyStates;
	windowEvent::EventStates WindowEvent::eventStates;

	void App::UpdateInput()
	{
		Input::Init(GetKeyStates());
		WindowEvent::Init(GetEventStates());
	}

	App::App(InternalGameLibHandlersPtr internalGameLibHandlersPtr)
		:internalGameLibHandlersPtr(internalGameLibHandlersPtr), view({ internalGameLibHandlersPtr }) {
		ResourceManager::Init(internalGameLibHandlersPtr);
		GameWorld::Init(gameWorldData);

	}

	App App::CreateApp(WindowData windowData) {
		std::optional<InternalGameLibHandlersPtr> internalGameLibHandlers = GameInitializer::Init(windowData);
		if (internalGameLibHandlers.has_value() == false) {
			throw "";
		}
		return App{ internalGameLibHandlers.value() };
	}
	App::~App()
	{
		GameShutDown::ShutDown(std::move(internalGameLibHandlersPtr));
	}

}