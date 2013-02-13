#ifndef HG_OBJECT_MODULE
#define HG_OBJECT_MODULE

#include "../Component.hpp"
#include "../utils.hpp"

#include <boost/filesystem.hpp>

class Module : public Component {
public:
	Module() : Component::Component() {}
	
	Module(const String& name, boost::filesystem::path source) : Component::Component(name, source) {}
	
	String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "module: " + Component::name + "";
		
		if (children) {
			result += " {\n";
			result += Component::representate_children(indent, children);
			result += utils::tab(indent) + "}\n";
		}
		
		return result;
	}
	
	Kind getType() {
		return Component::MODULE;
	}
};

#endif