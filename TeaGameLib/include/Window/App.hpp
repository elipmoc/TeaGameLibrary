#pragma once
#include "App/Actor.hpp"
#include"App/ProcessInput.hpp"
#include "App/EffectParams.hpp"
#include "../View.hpp"
#include "../InternalGameLib/FpsWaitTicks.hpp"
#include "../InternalGameLib/GameInitializer.hpp"
#include "../InternalGameLib/GameShutDown.hpp"
#include "../InternalGameLib/DrawService.hpp"

namespace teaGameLib {

	struct App {
	private:

		InternalGameLibHandlersPtr internalGameLibHandlersPtr;
		View view;
		App(InternalGameLibHandlersPtr internalGameLibHandlersPtr)
			:internalGameLibHandlersPtr(internalGameLibHandlersPtr), view({ internalGameLibHandlersPtr }) {}

	public:

		static App CreateApp(WindowData windowData) {
			std::optional<InternalGameLibHandlersPtr> internalGameLibHandlers = GameInitializer::Init(windowData);
			if (internalGameLibHandlers.has_value() == false) {
				throw "";
			}
			return App{ internalGameLibHandlers.value() };
		}


		template<typename StartActor, typename UpdateMsgFunc>
		void Start(StartActor startActor, UpdateMsgFunc updateMsgFunc) {
			using Msg = std::invoke_result_t<UpdateMsgFunc, float>;
			std::queue<Msg> queue;
			EffectHandler effectHandler{ GameStates{} };
			EffectParams<Msg> effectParams{ effectHandler,CreateCommonEffectMsgQueue<Msg>(queue) };
			int ticksCount = 0;
			auto model= startActor.InvokeInitFunc();
			while (effectParams.effectHandler.GetIsRunning()) {
				effectParams.effectHandler = EffectHandler::SetEventStates(std::move(effectParams.effectHandler), ProcessInput());
				startActor.InvokeSubscriptionFunc(model).InvokeRunFunc(effectParams);
				float deltaTime = FpsWaitTicks(ticksCount);
				effectParams.effectMsgQueue.InQueueMsg(updateMsgFunc(deltaTime));

				model = std::move(
					UpdateMsgQueue(queue, std::move(model), startActor, effectParams)
				);

				DrawService::Draw(
					internalGameLibHandlersPtr,
					effectHandler.GetBackGroundColor(),
					[&]() {startActor.InvokeViewFunc(model, view); }
				);
			}
			GameShutDown::ShutDown(std::move(internalGameLibHandlersPtr));
		}

	private:

		template<typename StartActor, typename Msg, typename Model>
		Model&& UpdateMsgQueue(std::queue<Msg>& queue, Model&& model, const StartActor startActor, EffectParams<Msg>& effectParams) {
			while (true) {
				auto optMsg = DeQueueMsg<Msg,Model>(queue);
				if (optMsg.has_value() == false)break;
				model = std::move(Update(std::move(model), optMsg.value(), startActor, effectParams));
			}
			return std::move(model);
		}

		template<typename StartActor, typename Msg, typename Model>
		Model&& Update(Model&& model, const Msg& msg, const StartActor startActor, EffectParams<Msg>& effectParams) {
			auto updateData
				= startActor.InvokeUpdateFunc(msg, std::move(model));
			model = std::move(updateData.model);
			updateData.cmd.InvokeRunFunc(effectParams);
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