#pragma once
#include "InternalGameLib/FpsWaitTicks.hpp"
#include "SDL/SDL.h"

namespace teaGameLib {

	int FpsWaitTicks(const int ticksCount)
	{
		//60fpsになるように待機
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

		//deltaTimeの計算
		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}

		return SDL_GetTicks();
	}
}