#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Variant.hpp"
#include "TeaGameLib/Algorithm.hpp"

namespace tea = teaGameLib;
using GameWorld = tea::GameWorld;
using Color = tea::Color;
using Vector2DFloat = tea::math::Vector2D<float>;
using tea::resource::TextureResource;

constexpr int windowWidth = 1024;
constexpr int windowWidthHalf = windowWidth / 2;
constexpr int windowHeight = 768;
constexpr int windowHeightHalf = windowHeight / 2;

//Model
using Model = struct {
	struct Sprite { std::optional<TextureResource> texture; }sprite;
};

struct MsgType {
	struct Update { float deltaTime; };
	struct LoadTexture { std::optional<TextureResource> texture; };
};

//Msg
using Msg = tea::Variant<MsgType::Update, MsgType::LoadTexture>;

//Cmd,Subの型省略
using Cmd = tea::Cmd<Msg>;
using Sub = tea::Sub<Msg>;

//Init関数
tea::UpdateData<Model, Msg> Init() {
	return {
		Cmd::Batch(
			tea::ResourceManager::GetTexturePtr<Msg>("test.png",[](auto texture) {return Msg{MsgType::LoadTexture{texture}}; }),
			GameWorld::SetBackGroundColor<Msg>(Color::Blue())
		),
		Model{
			{}
		}
	};
};

//Update関数
tea::UpdateData<Model, Msg> Update(Msg msg, Model model) {
	//Msgの種類をパターンマッチで処理分岐する
	ret_match(msg)->tea::UpdateData<Model, Msg> {
		case_expr(msg, MsgType::Update) {
			Cmd::None(),
				std::move(model)
		};
		case(msg, MsgType::LoadTexture) {
			TextureResource tex= msg.texture.value();
			return {Cmd::None(), Model{ {msg.texture} }};
		}
	}match_end;
};

//Subscription関数
Sub Subscription(const Model&) {
	return Sub::None();
};

//View関数
void View(const Model& model, tea::View& view) {
	if (model.sprite.texture.has_value())
		view.DrawSprite(model.sprite.texture.value(), { 0,0 });
};

int main(int, char**)
{
	//アプリケーションオブジェクト作成
	auto app = tea::App::CreateApp({ "Game Programming in C++ (Chapter 2)",100,100,windowWidth,windowHeight });
	//アプリケーションスタート
	app.Start(
		tea::Actor{ Init,Update,Subscription,View },
		//毎フレーム一回呼ばれるのでその時のメッセージを設定
		[](float deltaTime) {return Msg{ MsgType::Update{deltaTime} }; }
	);

	return 0;
}