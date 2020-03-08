#include "TeaGameLib/App.hpp"
#include "TeaGameLib/CmdBuilder.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/App/InternalGameLib/DrawPrimitive.hpp"

namespace tea = teaGameLib;

int main(int , char** )
{
	//Model
	using Model = struct { int x; int y; };

	//Msg
	using Msg = std::string;

	//モデル初期値
	Model initModel{ 0,0 };

	//Init関数
	const auto init = [&initModel]() {
		return tea::InitData{
			std::move(initModel),
			tea::WindowData{"TestWindow",100,100,1024,768}
		};
	};

	//Update関数
	const auto update = [](Msg msg, Model model) {
		using Cmd = tea::Cmd<Msg>;
		auto cmd = (
			//ウインドウのバツボタンが押されたとき
			msg == "QuitEvent" ?
			tea::CmdBuilder::EndGame<Msg>() :
			//毎フレーム呼ばれるアップデートの時
			msg == "Update" ?
			Cmd::None() :
			//右に移動
			msg == "RightMove" ?
			model.x += 5, Cmd::None() :
			//左に移動
			msg == "LeftMove" ?
			model.x -= 5, Cmd::None() :
			//上に移動
			msg == "UpMove" ?
			model.y -= 5, Cmd::None() :
			//下に移動c
			msg == "DownMove" ?
			model.y += 5, Cmd::None() :
			//その他
			Cmd::None()
			);
		return tea::UpdateData{
			std::move(model),
			cmd
		};
	};

	//Subscription関数
	const auto subscription = [](const Model& model) {
		return tea::Cmd<Msg>::Batch(
			tea::Input::KeyInput(tea::KeyCode::KEY_D, Msg{ "RightMove" }),
			tea::Input::KeyInput(tea::KeyCode::KEY_A, Msg{ "LeftMove" }),
			tea::Input::KeyInput(tea::KeyCode::KEY_W, Msg{ "UpMove" }),
			tea::Input::KeyInput(tea::KeyCode::KEY_S, Msg{ "DownMove" }),
			tea::WindowEvent::Quit(Msg{ "QuitEvent" })
		);
	};

	//View関数
	const auto view = [](const Model& model, auto& sdlHandlers) {
		tea::DrawBall(sdlHandlers, model.x, model.y, 15);
	};

	//アプリケーションスタート
	const auto app = tea::App{
		tea::Actor{init,update,subscription,view},Msg{"Update"}
	};

	return 0;
}