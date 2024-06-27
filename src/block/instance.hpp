#include <string>
#include <vector>

#include "./block.hpp"

class block_id {
	size_t id;

   public:
	constexpr block_id() : id(invalid) {}
	explicit constexpr block_id(size_t id) : id(id) {}
	constexpr operator size_t() const noexcept { return id; }
	bool operator<(block_id that) const noexcept { return id < that.id; }
	constexpr bool valid() const noexcept { return *this != invalid; };

	static const block_id invalid;
};

template <>
struct std::hash<block_id> {
	inline size_t operator()(const block_id &x) const { return x; }
};

constexpr const block_id block_id::invalid(-1);

struct Block {
	block_id id;
	const BlockType &type;
	std::vector<std::string> inputValues;

	Block(const BlockType &type)
		: type(type), inputValues(type.inputs.size()) {}
};

std::ostream &operator<<(std::ostream &os, const Block &b);
