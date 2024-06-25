#include <cstddef>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "block/library.hpp"

// this should be the max size_t value
constexpr size_t UNLINKED = -1;

struct Link {
    size_t prev = UNLINKED;
    size_t next = UNLINKED;
};

class Workspace {
    struct B { size_t id; };

    std::vector<B> blocks;

    std::map<size_t, Link> links;

    std::set<size_t> roots;

    public:

    const std::set<size_t>& getRoots() {
        return roots;
    }
    const std::vector<B>& getBlocks() {
        return blocks;
    }
    const std::map<size_t, Link>& getLinks() {
        return links;
    }

    size_t add(B block, size_t after = UNLINKED) {
        block.id = blocks.size();
        blocks.push_back(block);
        if (after == UNLINKED) {
            roots.insert(block.id);
        } else {
            insert(after, block.id);
        }
        return block.id;
    }

    void insert(size_t after, size_t block) {
        auto last = links[after].next;
        links[after].next = block;
        links[block].prev = after;

        while (links[block].next != UNLINKED) {
            block = links[block].next;
        }
        links[block].next = last;
    }
};


int main() {
    auto lib = BlockLibrary::fromFile("example_collection.json");

    Workspace w;

    auto col1 = w.add({});
    col1 = w.add({}, col1);
    col1 = w.add({}, col1);
    auto after = col1;
    col1 = w.add({}, col1);
    col1 = w.add({}, col1);

    auto col2 = w.add({});
    auto root2 = col2;
    col2 = w.add({}, col2);
    col2 = w.add({}, col2);
    col2 = w.add({}, col2);

    w.insert(after, root2);

    auto roots = w.getRoots();
    auto blocks = w.getBlocks();
    auto links = w.getLinks();
    size_t i = 1;
    for (auto &root : roots) {
        std::cout << "root " << i++ << std::endl;
        auto blockID = root;
        while (blockID != UNLINKED) {
            std::cout << blockID << std::endl;
            blockID = links[blockID].next;
        }
    }

/*
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
    });*/

    // std::cout << lib.blocks[1] << std::endl;
}
