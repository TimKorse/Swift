#ifndef HG_OBJECT_CLASS
#define HG_OBJECT_CLASS

#include "../Component.hpp"
#include "../utils.hpp"
#include "../Printer.hpp"

#include <boost/filesystem.hpp>

class Class : public Component {
public:
	Class() : Component::Component() {}
	Class(const String& name, boost::filesystem::path source) : Component::Component(name, source) {}
	
	// Representation
	String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "class: " + Component::name;

		if (children) {
			result += " {\n";
			result += Component::representate_children(indent, children);
			result += utils::tab(indent) + "}\n";
		}
		
		return result;
	}
	
	void generate() {
		if (Component::dest.empty()) {
			dest = Component::source.replace_extension("");
		}
		
		Printer header(dest.replace_extension(".hpp"));
		Printer source(dest.replace_extension(".cpp"));
		source.include(shared_from_this());
		header.guard_start(Component::shared_from_this());
		
		for (VRef::iterator it = Component::children.begin(); it != Component::children.end(); ++it) {
			switch ((*it)->getType()) {
				case Component::REFERENCE:
					header.declare((*it)->resolve());
					source.include((*it)->resolve());
					break;
			}
		}
		
		// Definition
		header.define_start(Component::shared_from_this());
		
		for (VRef::iterator it = Component::children.begin(); it != Component::children.end(); ++it) {
			switch ((*it)->getType()) {
				case Component::FUNCTION:
					header.declare(*it);
					source.define(*it);
					break;
				case Component::VARIABLE:
					header.declare(*it);
					break;
			}
		}
		
		header.define_end(Component::shared_from_this());
		
		header.namespace_close();
		header.guard_end();
		
		source.namespace_close();
	}
	
	Kind getType() {
		return Component::CLASS;
	}
};

#endif