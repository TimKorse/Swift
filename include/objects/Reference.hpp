#ifndef HG_OBJECT_REFERENCE
#define HG_OBJECT_REFERENCE

#include "../Component.hpp"
#include "../utils.hpp"

#include "Temp.hpp"

#include <iostream>

#include <exception>

class Reference : public Component {
	
public:
	p_Component ref;
	
	Reference(p_Component r) : Component::Component(r->name), ref(r) {
	}
	
	virtual String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "reference: (" + ref->representate(0, false) + ")";
		if (children) 
			result += " \n";
		return result;
	}
	
	virtual Kind getType() {
		return REFERENCE;
	}
	
	virtual p_Component resolve() {
		return ref;
	}
	
	virtual p_Component find(const String& name) throw (p_Error) {
		std::cout << "REFERENCE: " << name <<std::endl;
		return ref->find(name);
	}
	
	virtual p_Component set(p_Component other) throw (p_Error) {
		return ref->set(other);
	}
		
	virtual p_Component create(p_Component other) throw (p_Error) {
		return ref->create(other);
	}
};

#endif