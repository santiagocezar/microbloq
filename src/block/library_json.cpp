#include <nlohmann/json.hpp>

#include "library.hpp"

using json = nlohmann::json;

BlockLibrary BlockLibrary::fromStream(std::ifstream &stream) {
	json blockJson = json::parse(stream);
	std::vector<BlockType> blocks;

	for (auto &[name, block] : blockJson.items()) {
		auto builder = BlockType::create(name.c_str());
		block.at("description").get_to(builder.description);
		block.at("label").get_to(builder.label);
		blocks.push_back(builder.build());
	}

	return blocks;	// FIXME: this is ok??????!!
}
