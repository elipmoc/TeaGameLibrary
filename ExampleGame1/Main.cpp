#include "TeaGameLib/Window/App.hpp"
#include "TeaGameLib/GameWorld.hpp"
#include "TeaGameLib/Input.hpp"
#include "TeaGameLib/WindowEvent.hpp"
#include "TeaGameLib/Variant.hpp"
#include "TeaGameLib/Algorithm.hpp"

namespace tea = teaGameLib;
using GameWorld = tea::GameWorld;
using Color = tea::Color;
using Vector2DFloat= tea::math::Vector2D<float>;

constexpr int thickness = 15;
constexpr int paddleHeight = 100;
constexpr int paddleHeightHalf = paddleHeight / 2;
constexpr int windowWidth = 1024;
constexpr int windowWidthHalf = windowWidth/ 2;
constexpr int windowHeight = 768;
constexpr int windowHeightHalf = windowHeight / 2;

//Model
using Model = struct {
	struct Paddle { Vector2DFloat pos; float addY = 0.0f; } paddle;
	struct Ball { Vector2DFloat pos; Vector2DFloat addPos; } ball;
};

struct MsgType {
	struct Update { float deltaTime; };
	struct End {};
	using AddY = float;
};

//Msg
using Msg = tea::Variant<MsgType::AddY, MsgType::Update, MsgType::End>;

//Cmd,Subの型省略
using Cmd = tea::Cmd<Msg>;
using Sub = tea::Sub<Msg>;

//Init関数
tea::UpdateData<Model, Msg> Init() {
	return {
		Model{
			{{10,windowHeightHalf}},
			{{windowWidthHalf,windowHeightHalf},{-200.0f,235.0f}}
		} ,
		GameWorld::SetBackGroundColor<Msg>(Color::Blue())
	};
};

//paddleの座標更新
void UpdatePaddle(Model::Paddle& paddle, MsgType::Update updateMsg) {
	paddle.pos.y += paddle.addY * updateMsg.deltaTime * 300.0f;
	paddle.addY = 0;
	paddle.pos.y = tea::Clamp<float>(
		paddle.pos.y,
		paddleHeightHalf + thickness,
		windowHeight - paddleHeightHalf - thickness);
};

//ballの更新
Cmd UpdateBall(Model::Ball& ball, Vector2DFloat paddlePos, MsgType::Update updateMsg) {
	//ballの座標更新
	ball.pos += ball.addPos * updateMsg.deltaTime;
	//ballの壁・paddleの判定処理
	float diff = paddlePos.y - ball.pos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		diff <= paddleHeightHalf &&
		ball.pos.x <= 25.0f && ball.pos.x >= 20.0f &&
		ball.addPos.x < 0.0f
		)
		ball.addPos.x *= -1.0f;
	else if (ball.pos.x <= 0.0f)
		return GameWorld::EndGame<Msg>();

	else if (ball.pos.x >= (windowWidth - thickness) && ball.addPos.x > 0.0f)
		ball.addPos.x *= -1.0f;

	if (ball.pos.y <= thickness && ball.addPos.y < 0.0f)
		ball.addPos.y *= -1;
	else if (ball.pos.y >= (windowHeight - thickness) && ball.addPos.y > 0.0f)
		ball.addPos.y *= -1;
	return Cmd::None();
};

//Update関数
tea::UpdateData<Model, Msg> Update(Msg msg, Model model) {
	//Msgの種類をパターンマッチで処理分岐する
	ret_match(msg)->tea::UpdateData<Model, Msg> {
		//ゲーム終了する
		case_expr(msg, MsgType::End) { std::move(model), GameWorld::EndGame<Msg>() };
		case(msg, MsgType::Update) {
			UpdatePaddle(model.paddle, msg);
			auto cmd = UpdateBall(model.ball, model.paddle.pos, msg);
			return { std::move(model),cmd };
		};
		//paddleのキー入力での移動を溜めておく
		case_expr(msg, MsgType::AddY) {
			(model.paddle.addY += msg, std::move(model)), Cmd::None()
		};
	}match_end;
};

//Subscription関数
Sub Subscription(const Model&) {
	return Sub::Batch(
		//キー入力イベントがあったら各種メッセージを送る
		tea::Input::KeyInput(tea::KeyCode::KEY_W, Msg{ MsgType::AddY{-1.0f} }),
		tea::Input::KeyInput(tea::KeyCode::KEY_S, Msg{ MsgType::AddY{1.0f} }),
		tea::Input::KeyInput(tea::KeyCode::KEY_ESCAPE, Msg{ MsgType::End{} }),
		//Windowからの終了イベントがあった時、QuitEventメッセージを送る（バツボタンを押した時など)
		tea::WindowEvent::Quit(Msg{ MsgType::End{} })
	);
};

//View関数
void View(const Model& model, tea::View& view) {
	view.DrawRect((model.paddle.pos + Vector2DFloat{ 0,-paddleHeightHalf }).StaticCast<int>(), { thickness,paddleHeight }, Color::White());
	view.DrawRect({ 0,0 }, { windowWidth,thickness }, Color::White());
	view.DrawRect({ 0,windowHeight - thickness }, { windowWidth,thickness }, Color::White());
	view.DrawRect({ windowWidth - thickness,0 }, { thickness,windowHeight }, Color::White());
	view.DrawSquare(model.ball.pos.StaticCast<int>(), thickness, Color::White());
};

int main(int, char**)
{
	//アプリケーションオブジェクト作成
	auto app = tea::App::CreateApp({ "Game Programming in C++ (Chapter 1)",100,100,windowWidth,windowHeight });
	//アプリケーションスタート
	app.Start(
		tea::Actor{ Init,Update,Subscription,View },
		//毎フレーム一回呼ばれるのでその時のメッセージを設定
		[](float deltaTime) {return Msg{ MsgType::Update{deltaTime} }; }
	);

	return 0;
}