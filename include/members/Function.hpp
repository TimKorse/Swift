#ifndef HG_OBJECT_FUNCTION
#define HG_OBJECT_FUNCTION

#include "Component.hpp"
#include "Type.hpp"

#include "utils.hpp"

class Function : public Component {
public:
	Type type;
	Function(const String name, Type t) : type(t), Component::Component(name) {}
	
	virtual String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "function: (" + type.type->representate(0, false) + ") " + Component::name + "";
		
		if (children) {
			result += " {\n";
			result += Component::representate_children(indent, children);
			result += utils::tab(indent) + "}\n";
		}
		
		return result;
	}
	
	virtual Kind getType() {
		return Component::FUNCTION;
	}
};

#endif