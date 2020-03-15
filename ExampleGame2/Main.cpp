#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/ResourceManager.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Variant.hpp"
#include "TeaGameLib/UtilModel/AnimSpriteModel.hpp"
#include "Ship.cpp"
#include "BackGround.cpp"
#include "CommonMsg.hpp"

namespace tea = teaGameLib;
using GameWorld = tea::GameWorld;
using WindowEvent = tea::WindowEvent;
using Color = tea::Color;
using Vector2DFloat = tea::math::Vector2D<float>;
using tea::resource::TextureResource;
using tea::ResourceManager;

constexpr int windowWidth = 1024;
constexpr int windowWidthHalf = windowWidth / 2;
constexpr int windowHeight = 768;
constexpr int windowHeightHalf = windowHeight / 2;

//Model
using Model = struct {
	std::optional<ship::Model> ship;
	std::optional<backGround::Model> backGround1;
	std::optional<backGround::Model> backGround2;
};

struct MsgType {
	struct LoadShipTexture { std::vector<TextureResource> textures; };
	struct LoadBackGroundTexture { std::vector<TextureResource> textures; };
	struct LoadErrTexture { };
	struct End{};
};

//Msg
using Msg = tea::Variant<
	commonMsg::Update,
	MsgType::LoadShipTexture,
	MsgType::LoadBackGroundTexture,
	MsgType::LoadErrTexture,
	MsgType::End,
	ship::Msg
>;

//Cmd,Subの型省略
using Cmd = tea::Cmd<Msg>;
using Sub = tea::Sub<Msg>;

//Init関数
tea::UpdateData<Model, Msg> Init() {
	return {
		Cmd::Batch(
			ResourceManager::GetTextureResources<Msg>(
				{"Assets/Ship01.png","Assets/Ship02.png","Assets/Ship03.png","Assets/Ship04.png" },
				[](std::optional<std::vector<TextureResource>> textures) {
					return textures.has_value() ? Msg{ MsgType::LoadShipTexture{textures.value()} } : Msg{MsgType::LoadErrTexture{}};
				}
			),
			ResourceManager::GetTextureResources<Msg>(
				{"Assets/Farback01.png","Assets/Farback02.png","Assets/Stars.png"},
				[](std::optional<std::vector<TextureResource>> textures) {
					return textures.has_value() ? Msg{ MsgType::LoadBackGroundTexture{textures.value()} } : Msg{MsgType::LoadErrTexture{}};
				}
			)
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
		case(msg, commonMsg::Update) {
			model.ship = ship::Update(ship::Msg{ msg }, std::move(model.ship.value()));
			model.backGround1 = backGround::Update(backGround::Msg{ msg }, std::move(model.backGround1.value()));
			model.backGround2 = backGround::Update(backGround::Msg{ msg }, std::move(model.backGround2.value()));
			return { Cmd::None(), std::move(model) };
		}
		case(msg, MsgType::LoadShipTexture) {
			model.ship = ship::Init(std::move(msg.textures));
			return { Cmd::None(), std::move(model) };
		}
		case(msg, MsgType::LoadBackGroundTexture) {
			model.backGround1 = backGround::Init(std::move(msg.textures[0]), std::move(msg.textures[1]), 200.0f);
			model.backGround2 = backGround::Init(std::move(msg.textures[2]), std::move(msg.textures[2]),100.0f);
			return { Cmd::None(), std::move(model) };
		}
		case(msg, MsgType::LoadErrTexture) {
			throw "image file load error!";
		}
		case_expr(msg, MsgType::End)
		{
			GameWorld::EndGame<Msg>(), std::move(model)
		};
		case(msg, ship::Msg) {
			model.ship = ship::Update(msg, std::move(model.ship.value()));
			return { Cmd::None(),std::move(model) };
		}
	}match_end;
};

//Subscription関数
Sub Subscription(const Model& model) {
	if (model.ship.has_value())
		return Sub::Batch(
			ship::Subscription(model.ship.value()).Map<Msg>([](ship::Msg msg) {return Msg{ msg }; }),
			tea::WindowEvent::Quit(Msg{ MsgType::End{} })
		);
	return Sub::None();
};

//View関数
void View(const Model& model, tea::View& view) {
	if (model.backGround1.has_value())
		backGround::View(model.backGround1.value(), view);
	if (model.backGround2.has_value())
		backGround::View(model.backGround2.value(), view);
	if (model.ship.has_value())
		ship::View(model.ship.value(), view);
};

int main(int, char**)
{
	//アプリケーションオブジェクト作成
	auto app = tea::App::CreateApp({ "Game Programming in C++ (Chapter 2)",100,100,windowWidth,windowHeight });
	//アプリケーションスタート
	app.Start(
		tea::Actor{ Init,Update,Subscription,View },
		//毎フレーム一回呼ばれるのでその時のメッセージを設定
		[](float deltaTime) {return Msg{ commonMsg::Update{deltaTime} }; }
	);

	return 0;
}