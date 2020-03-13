#pragma once
#include "App/Actor.hpp"
#include "../View.hpp"
#include "../InternalGameLib/FpsWaitTicks.hpp"
#include "../InternalGameLib/DrawService.hpp"
#include "App/WindowData.hpp"
#include "App/EffectMsgQueueFactory/CreateCommonEffectMsgQueue.hpp"
#include "../GameWorld/GameWorldData.hpp"

namespace teaGameLib {

	template<typename Msg>
	std::optional<Msg> DeQueueMsg(std::queue<Msg>& queue) {
		if (queue.size() == 0)return std::optional<Msg>{std::nullopt};
		auto msg = queue.front();
		queue.pop();
		return std::optional<Msg>{msg};
	}

	template<typename StartActor, typename Msg, typename Model>
	Model&& UpdateMsgQueue(std::queue<Msg>& queue, Model&& model, const StartActor startActor, EffectMsgQueue<Msg>& effectMsgQueue) {
		while (true) {
			auto optMsg = DeQueueMsg<Msg>(queue);
			if (optMsg.has_value() == false)break;
			model = Update(std::move(model), optMsg.value(), startActor, effectMsgQueue);
		}
		return std::move(model);
	}

	template<typename StartActor, typename Msg, typename Model>
	Model&& Update(Model&& model, const Msg& msg, const StartActor startActor, EffectMsgQueue<Msg>& effectMsgQueue) {
		auto updateData
			= startActor.InvokeUpdateFunc(msg, std::move(model));
		model = std::move(updateData.model);
		updateData.cmd.InvokeRunFunc(effectMsgQueue);
		return std::move(model);
	}



	class App {
		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View view;
		gameWorld::GameWorldData gameWorldData;

		App(InternalGameLibHandlersPtr internalGameLibHandlersPtr);

	public:

		static App CreateApp(WindowData);

		template<typename StartActor, typename UpdateMsgFunc>
		void Start(StartActor startActor, UpdateMsgFunc updateMsgFunc) {
			using Msg = std::invoke_result_t<UpdateMsgFunc, float>;
			std::queue<Msg> queue;
			EffectMsgQueue<Msg> effectMsgQueue = CreateCommonEffectMsgQueue<Msg>(queue);
			int ticksCount = 0;
			auto [initCmd, model] = startActor.InvokeInitFunc();
			initCmd.InvokeRunFunc(effectMsgQueue);
			while (gameWorldData.GetIsRunning()) {
				UpdateInput();
				startActor.InvokeSubscriptionFunc(model).InvokeRunFunc(effectMsgQueue);
				float deltaTime = FpsWaitTicks(ticksCount);
				effectMsgQueue.InQueueMsg(updateMsgFunc(deltaTime));

				model =
					UpdateMsgQueue(queue, std::move(model), startActor, effectMsgQueue);

				DrawService::Draw(
					internalGameLibHandlersPtr,
					gameWorldData.GetBackGroundColor(),
					[&]() {startActor.InvokeViewFunc(model, view); }
				);
			}
		}

		~App();

	private:

		void UpdateInput();
	};
}