#include "Window/App/InternalGameLib/GameInitializer.hpp"
#include "SDLHandlers.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	bool InitSDL() {
		int sdlResult = SDL_Init(SDL_INIT_VIDEO);
		if (sdlResult != 0)
		{
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}
		return true;
	}

	SDL_Window* InitSDLWindow(const WindowData& windowData) {
		auto sdlWindowPtr = SDL_CreateWindow(
			windowData.title.c_str(),
			windowData.topLeftX,
			windowData.topLeftY,
			windowData.width,
			windowData.height,
			0
		);

		if (!sdlWindowPtr)
		{
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return nullptr;
		}
		return sdlWindowPtr;
	}

	SDL_Renderer* InitSDLRenderer(SDL_Window* sdlWindowPtr) {
		auto sdlRendererPtr = SDL_CreateRenderer(
			sdlWindowPtr,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);

		if (!sdlRendererPtr)
		{
			SDL_Log("Failed to create renderer: %s", SDL_GetError());
			return nullptr;
		}
		return sdlRendererPtr;
	}

	std::optional<InternalGameLibHandlersPtr> GameInitializer::Init(const WindowData& windowData)
	{
		if (!InitSDL())return std::nullopt;
		auto sdlWindowPtr = InitSDLWindow(windowData);
		if (!sdlWindowPtr)return std::nullopt;
		auto sdlRendererPtr = InitSDLRenderer(sdlWindowPtr);
		if (!sdlRendererPtr)return std::nullopt;
		return  new InternalGameLibHandlers{ sdlWindowPtr,sdlRendererPtr };
	}
}
