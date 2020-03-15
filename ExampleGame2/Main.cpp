#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/ResourceManager.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Variant.hpp"
#include "TeaGameLib/UtilModel/AnimSpriteModel.hpp"
#include "Ship.cpp"

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
	std::optional<ship::Model> ship;
};

struct MsgType {
	struct Update { float deltaTime; };
	struct LoadTexture { std::vector<TextureResource> textures; };
	struct LoadErrTexture { };
};

//Msg
using Msg = tea::Variant<MsgType::Update, MsgType::LoadTexture, MsgType::LoadErrTexture, ship::Msg>;

//Cmd,Subの型省略
using Cmd = tea::Cmd<Msg>;
using Sub = tea::Sub<Msg>;

//Init関数
tea::UpdateData<Model, Msg> Init() {
	return {
		Cmd::Batch(
			tea::ResourceManager::GetTextureResources<Msg>(
				{"Assets/Ship01.png","Assets/Ship02.png","Assets/Ship03.png","Assets/Ship04.png" },
				[](std::optional<std::vector<tea::resource::TextureResource>> textures) {
					return textures.has_value() ? Msg{ MsgType::LoadTexture{textures.value()} } : Msg{MsgType::LoadErrTexture{}};
				}
			),

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
		case(msg, MsgType::Update) {
			model.ship = ship::Update(ship::Msg{ ship::MsgType::Update{ msg.deltaTime } }, std::move(model.ship.value())).model;
			return { Cmd::None(), std::move(model) };
		}
		case(msg, MsgType::LoadTexture) {
			auto [_, shipModel] = ship::Init(std::move(msg.textures));
			model.ship = { std::move(shipModel) };
			return { Cmd::None(), std::move(model) };
		}
		case(msg, MsgType::LoadErrTexture) {
			throw "image file load error!";
		}
		case(msg, ship::Msg) {
			auto [cmd, shipModel] = ship::Update(msg, std::move(model.ship.value()));
			model.ship = { std::move(shipModel) };
			return { Cmd::None(),std::move(model) };
		}
	}match_end;
};

//Subscription関数
Sub Subscription(const Model& model) {
	if (model.ship.has_value())
		return ship::Subscription(model.ship.value()).Map<Msg>([](ship::Msg msg) {return Msg{ msg };});
	return Sub::None();
};

//View関数
void View(const Model& model, tea::View& view) {
	if (model.ship.has_value()) {
		ship::View(model.ship.value(), view);
	}
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