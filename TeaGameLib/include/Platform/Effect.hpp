#pragma once
#include <functional>
#include <optional>
#include "../Window/App/EffectParams.hpp"

namespace teaGameLib {
	template<typename Msg>
	class Effect {
	public:
		using OptMsg = std::optional<Msg>;
		using EffectMsg = Msg;
		using RunFunc = std::function<void(EffectParams<Msg>)>;
	private:
		const RunFunc runFunc;
	public:
		constexpr Effect(RunFunc runFunc) :runFunc(runFunc) {}
		constexpr Effect() :runFunc([](EffectParams<Msg> _) {}) {}

		void InvokeRunFunc(EffectParams<Msg> effectParams) const { runFunc(effectParams); };

		template<typename NewMsg>
		Effect<NewMsg> Map(std::function<NewMsg(Msg)> mapFunc)const {
			return Effect<NewMsg>{
				[runFunc = runFunc, mapFunc = mapFunc](EffectParams<NewMsg> effectParams) {
					runFunc(
						EffectParams<Msg>{effectParams.effectHandler, effectParams.effectMsgQueue.Map(mapFunc) }
					);
				}
			};
		}

		static Effect<Msg> Batch()
		{
			return Effect<Msg>{};
		}

		template<typename HeadEffect, typename... Effects>
		static Effect<Msg> Batch(HeadEffect headEffect, Effects... effects)
		{
			return Effect<Msg>{ [headEffect = headEffect, effects...] (EffectParams<Msg> effectParams) {
				headEffect.InvokeRunFunc(effectParams);
				Batch(effects...).InvokeRunFunc(effectParams);
			}};
		}

		static Effect<Msg> None() { return Effect<Msg>{}; }
		static Effect<Msg> Id(Msg msg) {
			return {
				[msg](EffectParams<Msg> effectParams) {effectParams.effectMsgQueue.InQueueMsg(msg); }
			};
		}
	};

	template<typename Msg>
	using Cmd = Effect<Msg>;

	template<typename Msg>
	using Sub = Effect<Msg>;
}