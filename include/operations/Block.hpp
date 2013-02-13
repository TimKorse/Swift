#ifndef HG_OBJECT_BLOCK
#define HG_OBJECT_BLOCK

#include "default.hpp"
#include "Component.hpp"
#include "utils.hpp"
#include "Printer.hpp"

class Block : public Component {
	String content;
public:
	Block(const String& c) : Component::Component(), content(c) {}
	
	// Representation
	String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "block: " + Component::name;

		if (children) {
			result += " {\n";
			result += Component::representate_children(indent, children);
			result += utils::tab(indent) + "}\n";
		}
		
		return result;
	}
	
	Kind getType() {
		return Component::BLOCK;
	}
};

#endif