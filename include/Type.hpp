#ifndef HG_TYPE
#define HG_TYPE

#include "Component.hpp"

class Type {
public:
	Type(p_Component t) : type(t->resolve()) {}
	
	p_Component type;
	
	enum Method {
		PLAIN,
		POINTER,
		REFERENCE
	};
	
	Method method;
	/*bool templated;
	std::vector<Type> template_args;*/
};

#endif //HG_TYPE