#ifndef HG_AST
#define HG_AST

#include "default.hpp"

#include <memory>

class AST {
	p_Object context;
	Stack<p_Object> scope;
public:	
	AST();
	~AST();
	
	
	/*
		Creates a component in the current scope.
		Throws an error if a component with the same name already is defined.
	*/
	void create(p_Component component) throw (p_Error);
	
	/*
		Creates a reference to a component which is located in another scope.
	*/
	void create_reference(p_Component component);
	
	/*
		Tries to find an component in the current scope.
		Will descend if told so.
		Throws an error if there is no match found.
	*/
	p_Object find(String name, bool desc = false) throw (p_Error);
	
	
	
	void push_scope(p_Component component);
	void pop_scope();
	//void set_scope(p_Component component);
	p_Component get_scope();
}

typedef std::shared_ptr<AST> p_AST;

#endif //HG_AST