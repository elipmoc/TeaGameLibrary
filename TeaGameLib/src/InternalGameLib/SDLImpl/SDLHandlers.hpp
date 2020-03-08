#pragma once

struct SDL_Window;
struct SDL_Renderer;

namespace teaGameLib {
	struct InternalGameLibHandlers {
		SDL_Window* const sdlWindowPtr;
		SDL_Renderer* const sdlRendererPtr;
	};
}