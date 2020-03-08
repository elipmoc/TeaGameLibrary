#pragma once
#include "App/Actor.hpp"
#include"App/ProcessInput.hpp"
#include "App/EffectParams.hpp"
#include "../InternalGameLib/FpsWaitTicks.hpp"
#include "../InternalGameLib/GameInitializer.hpp"
#include "../InternalGameLib/GameShutDown.hpp"
#include "../InternalGameLib/DrawService.hpp"

namespace teaGameLib {
	template<typename InitFunc, typename UpdateFunc, typename SubscriptionFunc, typename ViewFunc>
	struct App {

		using StartActor = Actor<InitFunc, UpdateFunc,SubscriptionFunc, ViewFunc>;
		using Msg = typename StartActor::Msg;
		using Model = typename StartActor::Model;
		using OptMsg = typename Cmd<Msg>::OptMsg;
		using CustomUpdateData = UpdateData<Model, Msg>;

		App(StartActor startActor, Msg updateMsg,WindowData windowData)
		{
			std::queue<Msg> queue;
			EffectHandler effectHandler{ GameStates{} };
			EffectParams<Msg> effectParams{ effectHandler,CreateCommonEffectMsgQueue<Msg>(queue) };
			int ticksCount = 0;
			InitData<Model> initData = startActor.InvokeInitFunc();
			Model&& model = std::move(initData.model);
			std::optional<InternalGameLibHandlersPtr> internalGameLibHandlers = GameInitializer::Init(windowData);
			if (internalGameLibHandlers.has_value()) {
				while (effectParams.effectHandler.GetIsRunning()) {
					effectParams.effectHandler = EffectHandler::SetEventStates(std::move(effectParams.effectHandler), ProcessInput());
					startActor.InvokeSubscriptionFunc(model).InvokeRunFunc(effectParams);
					ticksCount = FpsWaitTicks(ticksCount);
					effectParams.effectMsgQueue.InQueueMsg(updateMsg);

					model = std::move(
						UpdateMsgQueue(queue,std::move(model), startActor, effectParams)
					);

					DrawService::Draw(internalGameLibHandlers.value(), [&](auto& renderer) {startActor.InvokeViewFunc(model, renderer); });
				}
				GameShutDown::ShutDown(std::move(internalGameLibHandlers.value()));
			}
		}
	private:

		Model&& UpdateMsgQueue(std::queue<Msg>& queue, Model&& model, const StartActor startActor, EffectParams<Msg>& effectParams) {
			while (true) {
				OptMsg optMsg = DeQueueMsg(queue);
				if (optMsg.has_value() == false)break;
				model = std::move(Update(std::move(model), optMsg.value(), startActor, effectParams));
			}
			return std::move(model);
		}

		Model&& Update(Model&& model,const Msg& msg,const StartActor startActor, EffectParams<Msg>& effectParams) {
			CustomUpdateData updateData
				= startActor.InvokeUpdateFunc(msg, std::move(model));
			model = std::move(updateData.model);
			updateData.cmd.InvokeRunFunc(effectParams);
			return std::move(model);
		}

		std::optional<Msg> DeQueueMsg(std::queue<Msg>& queue) {
			if (queue.size() == 0)return std::optional<Msg>{std::nullopt};
			auto msg = queue.front();
			queue.pop();
			return std::optional<Msg>{msg};
		}

	};
}