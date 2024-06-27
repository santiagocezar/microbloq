#include "library.hpp"

template<size_t size>
BlockLibrary BlockLibrary::fromBuilders(const BlockType::Builder (& builders)[size]) {
    std::vector<BlockType> blocks;
    blocks.reserve(size);
    for (size_t i = 0; i < size; i++) {
        auto block = builders[i].finish();
        for (auto &input : block.inputs) {
        }
        blocks.push_back(block);
    }
    return blocks; //FIXME: this is ok??????!!
}

BlockLibrary BlockLibrary::fromFile(const char * path) {
    std::ifstream f(path);
    return fromStream(f);
}
