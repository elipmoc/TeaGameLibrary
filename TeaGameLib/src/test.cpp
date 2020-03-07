#include "test.hpp"
#include <iostream>
#include "SDL/SDL.h"

void Hoge() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	auto mWindow = SDL_CreateWindow(
		"Test", 
		100,	
		100,
		1024,
		768,
		0	
	);

	auto mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	auto mTicksCount = 0;
	while (true) {

		SDL_Event event;
		while (SDL_PollEvent(&event));

		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
		mTicksCount = SDL_GetTicks();

		SDL_SetRenderDrawColor(
			mRenderer,
			0,
			0,	
			255,
			255		
		);

		SDL_RenderClear(mRenderer);
		SDL_RenderPresent(mRenderer);

	}
}