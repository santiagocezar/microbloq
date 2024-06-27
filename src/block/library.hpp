#include <fstream>
#include <vector>

#include "./block.hpp"

class BlockLibrary {
   public:
	const std::vector<BlockType> blocks;

	BlockLibrary(std::vector<BlockType> blocks) : blocks(blocks) {}

	template <size_t size>
	static BlockLibrary fromBuilders(
		const BlockType::Builder (&builders)[size]);

	static BlockLibrary fromFile(const char *path);
	static BlockLibrary fromStream(std::ifstream &stream);
};
