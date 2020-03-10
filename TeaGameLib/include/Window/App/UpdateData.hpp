#pragma once

#include "../../Platform/Effect.hpp"

namespace teaGameLib {

	template<typename Model,typename Msg>
	struct UpdateData {
		const Cmd<Msg> cmd;
		Model model;
		UpdateData(Cmd<Msg> cmd, Model&& model) :model(std::move(model)), cmd(cmd) {};
		UpdateData(const UpdateData& updateData) :model(std::move(updateData.model)), cmd(updateData.cmd) {};
		UpdateData(UpdateData&&) = delete;
	};
}
