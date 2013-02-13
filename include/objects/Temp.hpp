#ifndef HG_OBJECT_TEMP
#define HG_OBJECT_TEMP

#include "../Component.hpp"
#include "../utils.hpp"

#include <vector>

class Temp : public Component {
	
public:
	std::vector<p_Component> references;
	
	Temp(const String& name) : Component::Component(name) {}
	
	String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "temp: " + Component::name + "";
		
		if (children) {
			result += " {\n";
			result += Component::representate_children(indent, children);
			result += utils::tab(indent) + "}\n";
		}
		
		return result;
	}
	
	Kind getType() {
		return Component::TEMP;
	}
};

#endif