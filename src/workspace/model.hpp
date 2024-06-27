#pragma once

#include <immer/map.hpp>
#include <immer/set.hpp>
#include <immer/vector.hpp>

#include "block/instance.hpp"

namespace workspace {

struct Link {
	block_id prev;
	block_id next;
};

struct Model {
	immer::vector<Block> blocks;

	immer::map<block_id, Link> links;

	immer::set<block_id> roots;

	/*
	const std::set<block_id>& getRoots() {
		return roots;
	}
	const std::vector<Block>& getBlocks() {
		return blocks;
	}
	const std::map<block_id, Link>& getLinks() {
		return links;
	}
	*/

	bool sanityCheck();
	void print();
};

}  // namespace workspace
