#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/View.hpp"
#include "TeaGameLib/Math/Vector2D.hpp"
#include "TeaGameLib/Variant.hpp"

namespace tea = teaGameLib;

template<typename T>
using Vector2D = tea::math::Vector2D<T>;

struct MsgType {
	struct Update {};
	struct End {};
	using AddPos = Vector2D<int>;
};

using Pos = Vector2D<int>;

int main(int , char** )
{
	//Model
	using Model = Pos;

	//Msg
	using Msg = tea::Variant<MsgType::AddPos, MsgType::Update, MsgType::End>;

	//Cmd,Subの型省略
	using Cmd = tea::Cmd<Msg>;
	using Sub = tea::Sub<Msg>;

	//モデル初期値
	Model initModel{ 512,384 };

	//Init関数
	const auto init = [&initModel]() {
		return std::move(initModel);
	};

	//Update関数
	const auto update = [](Msg msg, Model model) {
		return
			match(msg)->tea::UpdateData<Model, Msg> {
			case_expr(msg, MsgType::End) { std::move(model), tea::GameWorld::EndGame<Msg>() };
			case_expr(msg, MsgType::Update) { std::move(model), Cmd::None() };
			case_expr(msg, MsgType::AddPos) { model + msg * 5, Cmd::None() };
		}match_end(msg);
	};

	//Subscription関数
	const auto subscription = [](const Model& model) {
		using Input = tea::Input;
		using WindowEvent = tea::WindowEvent;

		return Cmd::Batch(
			//キー入力イベントがあったら各種メッセージを送る
			Input::KeyInput(tea::KeyCode::KEY_D, Msg{ MsgType::AddPos::Right() }),
			Input::KeyInput(tea::KeyCode::KEY_A, Msg{ MsgType::AddPos::Left() }),
			Input::KeyInput(tea::KeyCode::KEY_W, Msg{ MsgType::AddPos::Up() }),
			Input::KeyInput(tea::KeyCode::KEY_S, Msg{ MsgType::AddPos::Down() }),
			//Windowからの終了イベントがあった時、QuitEventメッセージを送る（バツボタンを押した時など)
			WindowEvent::Quit(Msg{ MsgType::End{} })
		);
	};

	//View関数
	const auto view = [](const Model& model, tea::View& view) {
		view.DrawBall(model.x, model.y, 15);
	};

	//アプリケーションオブジェクト作成
	auto app = tea::App::CreateApp({ "TestWindow",100,100,1024,768 });

	//アプリケーションスタート
	app.Start(
		tea::Actor{ init,update,subscription,view },
		Msg{ MsgType::Update{} }//毎フレーム一回呼ばれるのでその時のメッセージを設定
	);

	return 0;
}