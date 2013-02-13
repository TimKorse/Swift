#ifndef HG_OBJECT
#define HG_OBJECT

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Error.hpp"

#include <boost/filesystem.hpp>

class Component;
typedef boost::shared_ptr<Component> p_Component;
typedef std::vector<p_Component> VRef;

class Component : public boost::enable_shared_from_this<Component> {
	
public:
	boost::filesystem::path path; // Relative path
	boost::filesystem::path source; // Absolute source path
	boost::filesystem::path dest; // Absolute destination path (same as source if not set)
	
	String name;
	std::vector<p_Component> children;
	p_Component parent;
	
	enum Kind {
		BASE,
		
		OBJECT,
		TEMP,
		// Components
		MODULE,
		CLASS,
		INTERFACE,
		ENUM,
		
		MEMBER,
		// Members
		VARIABLE,
		PRIMITIVE,
		ARGUMENT,
		FUNCTION,
		
		// Operation
		BLOCK,
		
		// Other
		REFERENCE
	};
	
	Component() : name("...") {}
	Component(String n) : name(n) {
		//path /= name;
	}
	Component(String n, boost::filesystem::path s) : name(n), source(s) {
		//path /= name;
	}
	
	virtual ~Component() {}
	
	virtual void copy(p_Component other) {
		children = other->children;
		path = other->path;
		name = other->name;
	}
	
	virtual p_Component resolve();
	virtual VRef parents() {
		VRef v;
		p_Component i = shared_from_this()->resolve();
		while (i->parent != NULL) {
			i = i->parent->resolve();
			v.push_back(i);
		}
		return v;
	}
	
	virtual void generate();
	virtual p_Component find(const String& name, bool with_parents = true) throw (p_Error);
	virtual p_Component create(p_Component other);
	virtual p_Component set(p_Component other);
	//virtual Ref get(Ref other);
	
	virtual Kind getType();
	
	virtual String representate(int indent = 0, bool show_children = true) {
		return "Object!?\n";
	}
	
	String representate_children(int indent, bool show_children) {
		if (!show_children) return "";
		String result;
		for (std::vector<p_Component>::iterator it = children.begin(); it != children.end(); it++) {
			result += (*it)->representate(indent + 1, show_children);
		}
		return result;
	}
};

#endif //HG_OBJECT