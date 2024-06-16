#include "./block.hpp"

#include <vector>
#include <fstream>

class BlockLibrary {
public:
    const std::vector<Block> blocks;

    BlockLibrary(std::vector<Block> blocks) : blocks(blocks) {}

    template<size_t size>
    static BlockLibrary fromBuilders(const Block::Builder (& builders)[size]);

    static BlockLibrary fromFile(const char * path);
    static BlockLibrary fromStream(std::ifstream & stream);
};
