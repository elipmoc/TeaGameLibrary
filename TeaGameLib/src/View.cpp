#include "View.hpp"
#include "InternalGameLib/Interface/DrawPrimitive.hpp"
#include "InternalGameLib/Interface/DrawSprite.hpp"

namespace teaGameLib {
	void View::DrawSquare(const math::Vector2D<int>& v, const int length, const Color& color) {
		teaGameLib::DrawSquare(internalGameLibHandlersPtr, v, length, color);
	}
	void View::DrawRect(const math::Vector2D<int>& leftUpPos, const math::Vector2D<int>& size, const Color& color)
	{
		teaGameLib::DrawRect(internalGameLibHandlersPtr, leftUpPos, size, color);
	}
	void View::DrawSprite(const resource::TextureResource& textureResource, const math::Vector2D<int>& centerPos) {
		teaGameLib::DrawSprite(internalGameLibHandlersPtr, textureResource, centerPos);
	}
	void View::DrawSprite(const resource::TextureResource& textureResource, const math::Vector2D<int>& centerPos, double angle)
	{
		teaGameLib::DrawSprite(internalGameLibHandlersPtr, textureResource, centerPos,angle);
	}
	void View::DrawSprite(const resource::TextureResource& textureResource, const math::Vector2D<int>& centerPos, const math::Vector2D<float>& scale, double angle)
	{
		teaGameLib::DrawSprite(internalGameLibHandlersPtr, textureResource, centerPos, scale, angle);
	}
}