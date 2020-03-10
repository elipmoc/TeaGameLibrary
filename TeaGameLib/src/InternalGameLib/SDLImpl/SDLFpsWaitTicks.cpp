#pragma once
#include "InternalGameLib/FpsWaitTicks.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	float FpsWaitTicks(int& ticksCount)
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

		if (deltaTime > 0.05f)
			deltaTime = 0.05f;
		ticksCount = SDL_GetTicks();
		return deltaTime;
	}
}