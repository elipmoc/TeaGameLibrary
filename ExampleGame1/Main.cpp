#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Variant.hpp"

namespace tea = teaGameLib;

using Vector2DInt = tea::math::Vector2D<int>;

struct MsgType {
	struct Update { float deltaTime; };
	struct End {};
	using AddPos = Vector2DInt;
};

int main(int , char** )
{
	//Model
	using Model = Vector2DInt;

	//Msg
	using Msg = tea::Variant<MsgType::AddPos, MsgType::Update, MsgType::End>;

	//Cmd,Subの型省略
	using Cmd = tea::Cmd<Msg>;
	using Sub = tea::Sub<Msg>;

	//Init関数
	const auto init = []() {
		return Model{ 512,384 };
	};

	//Update関数
	const auto update = [](Msg msg, Model model) {
		//Msgの種類をパターンマッチで処理分岐する
		ret_match(msg)->tea::UpdateData<Model, Msg> {
			//ゲーム終了する
			case_expr(msg, MsgType::End) { std::move(model), tea::GameWorld::EndGame<Msg>() };
			//毎フレーム呼ばれるアップデート処理(今は特に何もしない)
			case_expr(msg, MsgType::Update) { std::move(model), Cmd::None() };
			//移動
			case_expr(msg, MsgType::AddPos) { model + msg * 5, Cmd::None() };
		}match_end;
	};

	//Subscription関数
	const auto subscription = [](const Model& model) {
		using Input = tea::Input;

		return Sub::Batch(
			//キー入力イベントがあったら各種メッセージを送る
			Input::KeyInput(tea::KeyCode::KEY_D, Msg{ MsgType::AddPos::Right() }),
			Input::KeyInput(tea::KeyCode::KEY_A, Msg{ MsgType::AddPos::Left() }),
			Input::KeyInput(tea::KeyCode::KEY_W, Msg{ MsgType::AddPos::Up() }),
			Input::KeyInput(tea::KeyCode::KEY_S, Msg{ MsgType::AddPos::Down() }),
			//Windowからの終了イベントがあった時、QuitEventメッセージを送る（バツボタンを押した時など)
			tea::WindowEvent::Quit(Msg{ MsgType::End{} })
		);
	};

	//View関数
	const auto view = [](const Model& model, tea::View& view) {
		view.DrawSquare(model, 15, tea::Color::Blue());
	};

	//アプリケーションオブジェクト作成
	auto app = tea::App::CreateApp({ "TestWindow",100,100,1024,768 });

	//アプリケーションスタート
	app.Start(
		tea::Actor{ init,update,subscription,view },
		//毎フレーム一回呼ばれるのでその時のメッセージを設定
		[](float deltaTime) {return Msg{ MsgType::Update{deltaTime} }; }
	);

	return 0;
}