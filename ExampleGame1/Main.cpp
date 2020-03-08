#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/View.hpp"

namespace tea = teaGameLib;

int main(int , char** )
{
	//Model
	using Model = struct { int x; int y; };

	//Msg
	using Msg = std::string;

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
	const auto update = [](Msg msg, Model model)->tea::UpdateData<Model, Msg> {
		//ゲーム終了をする
		if (msg == "QuitEvent")
			return { std::move(model),tea::GameWorld::EndGame<Msg>() };
		//右に移動
		if (msg == "RightMove")	model.x += 5;
		//左に移動
		if (msg == "LeftMove") model.x -= 5;
		//上に移動
		if (msg == "UpMove") model.y -= 5;
		//下に移動
		if (msg == "DownMove") model.y += 5;
		//毎フレーム呼ばれるアップデート
		if (msg == "Update"); //今は特に何もしない

		return { std::move(model),Cmd::None() };
	};

	//Subscription関数
	const auto subscription = [](const Model& model) {
		using Input = tea::Input;
		using WindowEvent = tea::WindowEvent;

		return Cmd::Batch(
			//キー入力イベントがあったら各種メッセージを送る
			Input::KeyInput(tea::KeyCode::KEY_D, Msg{ "RightMove" }),
			Input::KeyInput(tea::KeyCode::KEY_A, Msg{ "LeftMove" }),
			Input::KeyInput(tea::KeyCode::KEY_W, Msg{ "UpMove" }),
			Input::KeyInput(tea::KeyCode::KEY_S, Msg{ "DownMove" }),
			//Windowからの終了イベントがあった時、QuitEventメッセージを送る（バツボタンを押した時など)
			WindowEvent::Quit(Msg{ "QuitEvent" })
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
		Msg{ "Update" }//毎フレーム一回呼ばれるのでその時のメッセージを設定
	);

	return 0;
}