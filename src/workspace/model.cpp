#include "model.hpp"

#include <iostream>

namespace workspace {

bool Model::sanityCheck() {
	block_id prev;

	for (auto block : roots) {
		if (!block.valid()) {
			std::cerr << "warn: UNLINKED is a root" << std::endl;
			return false;
		}
		while (block.valid()) {
			if (links[block].prev != prev) {
				std::cerr << "warn: prev link for block ID " << block
						  << " is inconsistent" << std::endl;
				return false;
			}
			prev = block;
			block = links[block].next;
		}
	}
	return true;
}
void Model::print() {
	size_t i = 1;
	for (auto &root : roots) {
		std::cout << "root " << i++ << ":" << std::endl;
		auto bid = root;
		while (bid.valid()) {
			std::cout << blocks[bid] << std::endl;
			bid = links[bid].next;
		}
	}
}

}  // namespace workspace
