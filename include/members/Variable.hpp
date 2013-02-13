#ifndef HG_OBJECT_VARIABLE
#define HG_OBJECT_VARIABLE

#include "Component.hpp"
#include "utils.hpp"
#include "Type.hpp"

class Variable : public Component {
public:
	Type type;
	Variable(const String name, Type t) : type(t), Component::Component(name) {}
	
	virtual String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "variable: " + "(" + type.type->representate(0, false) + ") " + Component::name + "";
		if (children) 
			result += " \n";
		return result;
	}
	
	virtual Kind getType() {
		return Component::VARIABLE;
	}
};

#endif