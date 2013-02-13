#ifndef HG_OBJECT_PRIMITIVE
#define HG_OBJECT_PRIMITIVE

#include "../Component.hpp"
#include "../utils.hpp"

class Primitive : public Component {
public:
	Primitive(const String& name) : Component::Component(name) {}
	
	String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "primitive: " + Component::name + "";
		if (children) 
			result += "\n";
		return result;
	}
	
	Kind getType() {
		return PRIMITIVE;
	}
};

#endif