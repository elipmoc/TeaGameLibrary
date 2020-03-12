#pragma once
#include <functional>
#include <optional>
#include "../Window/App/EffectMsgQueue.hpp"

namespace teaGameLib {
	template<typename Msg>
	class Effect {
	public:
		using OptMsg = std::optional<Msg>;
		using EffectMsg = Msg;
		using RunFunc = std::function<void(EffectMsgQueue<Msg>)>;
	private:
		const RunFunc runFunc;
	public:
		constexpr Effect(RunFunc runFunc) :runFunc(runFunc) {}
		constexpr Effect() : runFunc([](EffectMsgQueue<Msg> _) {}) {}

		void InvokeRunFunc(EffectMsgQueue<Msg> effectMsgQueue) const { runFunc(effectMsgQueue); };

		template<typename NewMsg>
		Effect<NewMsg> Map(std::function<NewMsg(Msg)> mapFunc)const {
			return Effect<NewMsg>{
				[runFunc = runFunc, mapFunc = mapFunc](EffectMsgQueue<NewMsg> effectMsgQueue) {
					runFunc(
						EffectMsgQueue<Msg>{effectMsgQueue.Map(mapFunc) }
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
			return Effect<Msg>{ [headEffect = headEffect, effects...] (EffectMsgQueue<Msg> effectMsgQueue) {
				headEffect.InvokeRunFunc(effectMsgQueue);
				Batch(effects...).InvokeRunFunc(effectMsgQueue);
			}};
		}

		static Effect<Msg> None() { return Effect<Msg>{}; }
		static Effect<Msg> Id(Msg msg) {
			return {
				[msg](EffectMsgQueue<Msg> effectMsgQueue) {effectMsgQueue.InQueueMsg(msg); }
			};
		}
	};

	template<typename Msg>
	using Cmd = Effect<Msg>;

	template<typename Msg>
	using Sub = Effect<Msg>;
}