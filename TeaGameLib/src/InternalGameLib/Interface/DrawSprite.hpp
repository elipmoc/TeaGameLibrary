#pragma once
#include "../include/InternalGameLib/InternalGameLibHandlers.hpp"
#include "InternalGameLib/Resource/TextureResource.hpp"
#include "Math/Vector2D.hpp"

namespace teaGameLib {
	void DrawSprite(InternalGameLibHandlersPtr&, const resource::TextureResource&, const math::Vector2D<int>& centerPos);
}