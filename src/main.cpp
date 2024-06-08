#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <format>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using std::optional;
using std::vector;
using std::string;
using std::format;

struct Input {
    const char* const name;
    const char* const type;
    const char* const defaultValue;

    Input(const char* name,
          const char* type,
          const char* defaultValue) :
          name(name),
          type(type),
          defaultValue(defaultValue) {}
};

struct Output {
	const char* const type;

    Output(const char* type) :
           type(type) {}
};

struct Block {
    const int id = -1;

    const char* const name;
    const char* const description;
    const char* const label;
    const bool start;
    const bool end;
    const bool childrenAllowed;

    const vector<Input>    inputs;
    const optional<Output> output;
};

std::ostream& operator<<(std::ostream& os, const Block& b) {
    string label(b.label), replaced, replaceWith;
    size_t pos = 0, input = 1;
    while (true) {
        replaced = format("%{}", input);
        pos = label.find(replaced);
        if (pos == string::npos) break;
        if (input > b.inputs.size()) break;

        std::cout << "pos: " << pos << "\n";

        label.replace(
            pos, replaced.size(),
            replaceWith = format("({})", b.inputs[input - 1].name)
        );
        input ++;
    }
    os << label;
    return os;
}

class BlockBuilder {
    int id = -1;

    const char* name;
    const char* description;
    const char* label;
    bool start = false;
    bool end = false;
    bool childrenAllowed = false;

    vector<Input>    inputs;
    optional<Output> output;

public:
    BlockBuilder(const char* name, const char* description) : name(name), description(description) {}

    BlockBuilder& withLabel (const char* text) {
        label = text;
        return *this;
    }
    BlockBuilder& isStart () {
        start = true;
        return *this;
    }
    BlockBuilder& isEnd () {
        end = true;
        return *this;
    }
    BlockBuilder& allowsChildren () {
        childrenAllowed = true;
        return *this;
    }
    BlockBuilder& addInput (Input input) {
        inputs.emplace_back(input);
        return *this;
    }
    BlockBuilder& withOutput (const char* type) {
        output.emplace(Output(type));
        return *this;
    }
    Block finish () const {
        return {
            .id = id,
            .name = name,
            .label = label,
            .start = start,
            .end = end,
            .childrenAllowed = childrenAllowed,
            .inputs = inputs,
            .output = output,
        };
    }
};

template<size_t size>
vector<Block> finishBlocks(const BlockBuilder (& builders)[size]) {
    vector<Block> blocks;
    blocks.reserve(size);
    for (size_t i = 0; i < size; i++) {
        auto block = builders[i].finish();
        std::cout << "block " << block.label << " has these inputs:\n";
        for (auto &input : block.inputs) {
            std::cout << "  " << input.name << ": " << input.type << "\n";
        }
        blocks.push_back(block);
    }
    return blocks;
}

class BlockCollection {
public:
    const vector<Block> blocks;

    template<size_t size>
    BlockCollection(const BlockBuilder (& builders)[size]) : blocks(finishBlocks<size>(builders)) {}
};

int main() {
    std::ifstream f("example_collection.json");
    json blockJson = json::parse(f);

    for (auto &[name, block] : blockJson.items()) {
        BlockBuilder(name.c_str()
    }

    BlockCollection blocks ({
        BlockBuilder("WHILE_LOOP", "Repite cierta acción mientras que la condición resulte verdadera")
            .withLabel("repetir mientras %1")
            .addInput({"COND", "bool", "true"})
            .allowsChildren(),
        BlockBuilder("  FOR_LOOP", "Repite cierta acción un número definido de veces")
            .withLabel("repetir %1 veces")
            .addInput({"COUNT", "number", "10"})
            .allowsChildren(),
        BlockBuilder("MOVE_UNITS", "Mover el cierta cantidad de unidades")
            .withLabel("mover %1 unidades")
            .addInput({"AMOUNT", "number", "10"}),
        BlockBuilder("ROTATE_DEGREES", "Rotar en sentido antihorario cierto ángulo")
            .withLabel("rotar %1 grados")
            .addInput({"AMOUNT", "number", "15"})
    });

    std::cout << blocks.blocks[1] << std::endl;
}
