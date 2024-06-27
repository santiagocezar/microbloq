#include "actions.hpp"

#include <utility>

namespace workspace {


immer::map<block_id, Link> setPrev(immer::map<block_id, Link> links, block_id from, block_id to) {
    return std::move(links).update(from, [&] (auto l) {
        l.prev = to;
        return l;
    });
}
immer::map<block_id, Link> setNext(immer::map<block_id, Link> links, block_id from, block_id to) {
    return std::move(links).update(from, [&] (auto l) {
        l.next = to;
        return l;
    });
}

Model _update(Model m, LinkAction a) {
    if (a.id == a.after) return m; // No.

    // Unlink the previous block from this
    m.links = setPrev(m.links, m.links[a.id].prev, block_id::invalid);
    // Link to the new previous block
    m.links = setPrev(m.links, a.id, a.after);

    // If it's unlinked, add as a root and that's it
    if (!a.after.valid()) {
        m.roots = m.roots.insert(a.id);
        return m;
    }

    // Remove from the roots (should work even if it's not a root block)
    m.roots = m.roots.erase(a.id);

    // Blocks are moved in piles, we need to find the last one
    auto last = a.id;
    while (m.links[last].next.valid()) {
        last = m.links[last].next;
    }

    // Now link the next block
    m.links = setNext(m.links, last, m.links[a.after].next);
    m.links = setPrev(m.links, m.links[last].next, a.id);
    m.links = setNext(m.links, a.after, a.id);
    return m;
}

Model _update(Model m, AddAction a) {
    a.block.id = block_id(m.blocks.size());
    m.blocks = m.blocks.push_back(a.block);
    if (!a.after.valid()) {
        m.roots = m.roots.insert(a.block.id);
    } else {
        m = _update(m, LinkAction {
            .id = a.block.id,
            .after = a.after,
        });
    }

    return m;
}

Model update(Model m, Action a)
{
    return std::visit([&] (auto a) { return _update(m, a); }, a);
}

}
