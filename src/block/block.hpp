#pragma once

#include <optional>
#include <string>
#include <vector>

struct Input {
	const std::string name;
	const std::string type;
	const std::string defaultValue;

	Input(const std::string name, const std::string type,
		  const std::string defaultValue)
		: name(name), type(type), defaultValue(defaultValue) {}
};

struct BlockType {
	const std::string id;
	const std::string description;
	const std::string label;
	const bool start;
	const bool end;
	const bool childrenAllowed;

	const std::vector<Input> inputs;
	const std::optional<std::string> outputType;

	class Builder {
		friend BlockType;

		inline Builder &setID(const char *text) {
			id = text;
			return *this;
		}

	   public:
		std::string id;
		std::string description;
		std::string label;
		bool start;
		bool end;
		bool childrenAllowed;

		std::vector<Input> inputs;
		std::optional<std::string> outputType;

		inline Builder &reset() {
			id = {};
			description = {};
			label = {};
			start = false;
			end = false;
			childrenAllowed = false;
			inputs.clear();
			outputType.reset();
			return *this;
		}
		inline Builder &withLabel(const char *text) {
			label = text;
			return *this;
		}
		inline Builder &setDescription(const char *text) {
			description = text;
			return *this;
		}
		inline Builder &isStart() {
			start = true;
			return *this;
		}
		inline Builder &isEnd() {
			end = true;
			return *this;
		}
		inline Builder &allowsChildren() {
			childrenAllowed = true;
			return *this;
		}
		inline Builder &addInput(Input input) {
			inputs.emplace_back(input);
			return *this;
		}
		inline Builder &withOutput(const char *type) {
			outputType.emplace(type);
			return *this;
		}
		inline BlockType build() const {
			return {
				.id = id,
				.description = description,
				.label = label,
				.start = start,
				.end = end,
				.childrenAllowed = childrenAllowed,
				.inputs = inputs,
				.outputType = outputType,
			};
		}
	};

	static Builder &createAnother(const char *name) {
		static Builder blockBuilder;
		return blockBuilder.setID(name);
	}
	static Builder &create(const char *name) {
		return createAnother(name).reset();
	}
};

std::ostream &operator<<(std::ostream &os, const BlockType &b);
