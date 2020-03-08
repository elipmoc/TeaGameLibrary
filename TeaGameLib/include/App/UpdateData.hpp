#pragma once

#include "Effect.hpp"

namespace teaGameLib {

	template<typename Model,typename Msg>
	struct UpdateData {
		Model model;
		const Cmd<Msg> cmd;
		UpdateData(Model&& model, Cmd<Msg> cmd) :model(std::move(model)), cmd(cmd) {};
		UpdateData(const UpdateData& updateData) :model(std::move(updateData.model)), cmd(updateData.cmd) {};
		UpdateData(UpdateData&&) = delete;
	};
}
