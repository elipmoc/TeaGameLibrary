#pragma once
#include "App/Actor.hpp"
#include"App/ProcessInput.hpp"
#include "../Input.hpp"
#include "../WindowEvent.hpp"
#include "../InternalGameLib/FpsWaitTicks.hpp"
#include "../InternalGameLib/DrawService.hpp"
#include "App/WindowData.hpp"
#include "App/EffectMsgQueueFactory/CreateCommonEffectMsgQueue.hpp"
#include "App/EffectHandler.hpp"

namespace teaGameLib {
	class App {
		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View view;
		EffectHandler effectHandler;

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
			while (effectHandler.GetIsRunning()) {
				GameStates gameStates = ProcessInput();
				Input::Init(gameStates.keyStates);
				WindowEvent::Init(gameStates.eventStates);
				startActor.InvokeSubscriptionFunc(model).InvokeRunFunc(effectMsgQueue);
				float deltaTime = FpsWaitTicks(ticksCount);
				effectMsgQueue.InQueueMsg(updateMsgFunc(deltaTime));

				model = std::move(
					UpdateMsgQueue(queue, std::move(model), startActor, effectMsgQueue)
				);

				DrawService::Draw(
					internalGameLibHandlersPtr,
					effectHandler.GetBackGroundColor(),
					[&]() {startActor.InvokeViewFunc(model, view); }
				);
			}
		}

		~App();

	private:

		template<typename StartActor, typename Msg, typename Model>
		Model&& UpdateMsgQueue(std::queue<Msg>& queue, Model&& model, const StartActor startActor, EffectMsgQueue<Msg>& effectMsgQueue) {
			while (true) {
				auto optMsg = DeQueueMsg<Msg,Model>(queue);
				if (optMsg.has_value() == false)break;
				model = std::move(Update(std::move(model), optMsg.value(), startActor, effectMsgQueue));
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

		template<typename Msg, typename Model>
		std::optional<Msg> DeQueueMsg(std::queue<Msg>& queue) {
			if (queue.size() == 0)return std::optional<Msg>{std::nullopt};
			auto msg = queue.front();
			queue.pop();
			return std::optional<Msg>{msg};
		}
	};
}