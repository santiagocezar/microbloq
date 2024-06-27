#pragma once

#include <variant>

#include "model.hpp"

namespace workspace {

struct AddAction {
	Block block;
	block_id after;
};

struct LinkAction {
	block_id id;
	block_id after;
};

using Action = std::variant<AddAction, LinkAction>;

Model update(Model m, Action a);

}  // namespace workspace
