#include "./block.hpp"

#include <format>

std::ostream& operator<<(std::ostream& os, const Block& b) {
    std::string label(b.label), replaced, replaceWith;
    size_t pos = 0, input = 1;
    while (true) {
        replaced = std::format("%{}", input);
        pos = label.find(replaced);
        if (pos == std::string::npos) break;
        if (input > b.inputs.size()) break;

        label.replace(
            pos, replaced.size(),
                      replaceWith = format("({})", b.inputs[input - 1].name)
        );
        input ++;
    }
    os << label;
    return os;
}
