#pragma once
#include "UpdateData.hpp"

namespace teaGameLib {
	struct View;

	template<typename InitFunc, typename UpdateFunc, typename SubscriptionFunc, typename ViewFunc>
	struct Actor {
	private:
		const InitFunc initFunc;
		const UpdateFunc updateFunc;
		const SubscriptionFunc subscriptionFunc;
		const ViewFunc viewFunc;
	public:
		using Model = std::remove_reference_t<decltype(std::invoke_result_t<InitFunc>::model)>;
		using Msg = typename std::invoke_result_t<SubscriptionFunc, Model>::EffectMsg;

		Actor(
			InitFunc initFunc,
			UpdateFunc updateFunc,
			SubscriptionFunc subscriptionFunc,
			ViewFunc viewFunc
		) :
			initFunc(initFunc),
			updateFunc(updateFunc),
			subscriptionFunc(subscriptionFunc),
			viewFunc(viewFunc) {}

		UpdateData<Model,Msg> InvokeInitFunc()const { return initFunc(); }
		UpdateData<Model, Msg> InvokeUpdateFunc(Msg msg, Model&& model)const { return updateFunc(msg, std::move(model)); }
		void  InvokeViewFunc(const Model& model, View& view)const { viewFunc(model, view); }
		Sub<Msg> InvokeSubscriptionFunc(const Model& model)const { return subscriptionFunc(model); }
	};
};