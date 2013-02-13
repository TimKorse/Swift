#include "Component.hpp"
#include <iostream>
#include "Parser.hpp"

p_Component Component::find(const String& name, bool with_parents) throw (p_Error) {
	for (std::vector<p_Component>::iterator it = children.begin(); it != children.end(); it++) {
		if ((*it)->name == name)
			return *it;
	}
	
	if (with_parents && (parent != NULL))
		return parent->find(name, with_parents);
	else
		throw p_Error(new UndefinedObject(name));
}

p_Component Component::set(p_Component other) {
	for (std::vector<p_Component>::iterator it = children.begin(); it != children.end(); it++) {
		if ((*it)->name == other->name)
		{
			other->copy(*it);
			other->parent = shared_from_this();
			children.erase(it);
			children.push_back(other);
			return other;
		}
	}
	throw p_Error(new UndefinedObject(other->name));
}

p_Component Component::resolve() {
	return shared_from_this();
}

void Component::generate() {
	for (std::vector<p_Component>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->generate();
	}
}

p_Component Component::create(p_Component other) {
	for (std::vector<p_Component>::iterator it = children.begin(); it != children.end(); it++) {
		if ((*it)->name == other->name)
		{
			throw p_Error(new MultipleDefinition(name));
		}
	}
	other->parent = shared_from_this();
	other->path = path / other->name;
	children.push_back(other);
	return other;
}


Component::Kind Component::getType() {
	return OBJECT;
}

String utils::tab(int times) {
        String result = "";
        for (int i = 0; i < times; ++i) {
                result.push_back('\t');
        }
        return result;
}