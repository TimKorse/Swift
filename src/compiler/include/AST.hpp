#ifndef HG_AST
#define HG_AST

#include "default.hpp"

#include <memory>

class AST {
	p_Object context;
	p_Object scope;
public:	
	AST();
	~AST();
	
	
	/*
		Creates a component in the current scope.
	*/
	void create(p_Component component);
	
	/*
		creates a reference to a component which is located in another scope.
	*/
	void create_reference(p_Component component);
	
	/*
		Tries to find an component in the current scope.
		Will descend if told so.
		Throws an error if noone match.
	*/
	p_Object find(String name, bool desc = false) throw (p_Error);
	
	
	
	void set_scope(p_Object to);
	
	p_Object get_scope();
}

typedef std::shared_ptr<AST> p_AST;

#endif //HG_AST