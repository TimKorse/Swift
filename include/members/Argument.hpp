#ifndef HG_OBJECT_ARGUMENT
#define HG_OBJECT_ARGUMENT

#include "Component.hpp"
#include "utils.hpp"

#include "Type.hpp"

class Argument : public Component {
public:
	Type type;
	Argument(const String name, Type t) : type(t), Component::Component(name) {}
	
	virtual String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "argument: (" + type.type->representate(0, false) + ") " + Component::name + "";
		if (children) 
			result += " \n";
		return result;
	}
	
	virtual Kind getType() {
		return Component::ARGUMENT;
	}
};

#endif