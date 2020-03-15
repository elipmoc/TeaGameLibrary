#pragma once
#include "TeaGameLib/InternalGameLib/Resource/TextureResource.hpp"
#include "TeaGameLib/View.hpp"
#include "CommonMsg.hpp"

namespace backGround {

	namespace tea = teaGameLib;
	using tea::resource::TextureResource;
	using tea::math::Vector2D;

	struct Model {
		Vector2D<float>pos;
		Vector2D<float>posOffset;
		TextureResource texture1;
		TextureResource texture2;
		float speed;
	};

	using Msg = commonMsg::Update;

	inline Model Init(TextureResource&& texture1, TextureResource&& texture2,const float speed) {
		return Model{
			{static_cast<float>(texture1.GetWidth()) / 2.0f,static_cast<float>(texture1.GetHeight()) / 2.0f},
			{0,0},
			texture1,
			texture2,
			speed
		};
	}

	inline Model Update(Msg msg, Model&& model) {
		model.posOffset += Vector2D<float>{model.speed, 0.0f}*msg.deltaTime;
		if (model.posOffset.x > 1024.0f) { 
			model.posOffset.x = 0.0f; 
			auto tmp = std::move(model.texture1);
			model.texture1 = std::move(model.texture2);
			model.texture2 = std::move(tmp);
		}
		return std::move(model);
	}

	inline void View(const Model& model, tea::View& view) {
		view.DrawSprite(model.texture1, (model.pos + model.posOffset).StaticCast<int>());
		view.DrawSprite(model.texture2, (model.pos + model.posOffset - Vector2D<float>{1024.0f, 0.0f}).StaticCast<int>());
	}
}