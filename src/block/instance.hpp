#include <string>
#include <vector>

#include "./block.hpp"

struct BlockInstance {
    const std::string &id;
    std::vector<std::string> inputValues;

    BlockInstance(const Block &block) : id(block.id), inputValues(block.inputs.size()) {}
};
