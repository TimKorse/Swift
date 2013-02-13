#ifndef HG_PRINTER
#define HG_PRINTER

#include <fstream>
#include <boost/algorithm/string.hpp>

#include "default.hpp"
#include "Component.hpp"
#include "utils.hpp"
#include "members/Function.hpp"
#include "members/Argument.hpp"
#include "members/Variable.hpp"

#include "Type.hpp"

class Printer {
	Path dest;
	std::fstream output;
	int indent;
	p_Component current_namespace;
	
	String header_guard;
	String name_guard;
	String private_guard;
	
public:
	Printer(boost::filesystem::path d) : dest(d), indent(0) {
		output.open(dest.string().c_str(), std::ios_base::out|std::ios_base::trunc );
		header_guard = "HG_SWIFT_";
		name_guard = "";//"ng_swift_";
		private_guard = "pg_swift_";
	}
	
	void guard_start(p_Component o) {
		String name = header_guard;
		VRef names = o->parents();
		
		for (VRef::reverse_iterator it = names.rbegin(); it != names.rend(); ++it) {
			name += boost::to_upper_copy((*it)->name) + "_";
		}
		name += boost::to_upper_copy(o->name);
		
		output << "#ifndef " << name << std::endl;
		output << "#define " << name << std::endl << std::endl;
		output << "#include <engine/include.hpp>" << std::endl;
	}
	
	
	
	void guard_end() {
		output << std::endl << "#endif //" << header_guard << "*" << std::endl;
	}
	
	void include(p_Component o) {
		output << "#include <lib/" << o->path.string() << ".hpp>" << std::endl;
	}
	
	void namespace_set(p_Component o) {
		VRef parents = o->parents();
		while (current_namespace != NULL) {
			for (VRef::iterator it = parents.begin(); it != parents.end(); ++it) {
				if (*it == current_namespace) {
					while (it != parents.begin()) {
						namespace_start(*(--it));
					}
					return;
				}
			}
			String ns = current_namespace->name;
			namespace_end();
		}
		for (VRef::reverse_iterator it = parents.rbegin(); it != parents.rend(); ++it) {
			namespace_start(*it);
		}
	}
	
	void namespace_start(p_Component o) {
		if (o->getType() != Component::MODULE && o->getType() != Component::BASE)
			return;
		current_namespace = o;
		output << std::endl << utils::tab(indent++) << "namespace " << name_guard << o->name << " {" << std::endl;
	}
	
	void namespace_end() {
		current_namespace = current_namespace->parent;
		//if (current_namespace->getType() == Object::BASE)
		//	current_namespace.reset();
		output << utils::tab(--indent) << '}' << std::endl; 
	}
	
	void namespace_close() {
		while (current_namespace) {
			namespace_end();
		}
	}
	
	void declare(p_Component o) {
		switch (o->getType()) {
			case Component::CLASS:
			{
				namespace_set(o);
				output << utils::tab(indent) << "class " << name_guard << o->name << ';' << std::endl;
				break;
			}
			
			case Component::VARIABLE:
			{
				boost::shared_ptr<Variable> v = boost::dynamic_pointer_cast<Variable>(o);
				output << utils::tab(indent) << type_of(v->type) << " " << name_guard << o->name << ";" << std::endl;
				break;
			}
			
			case Component::FUNCTION:
			{
				boost::shared_ptr<Function> f = boost::dynamic_pointer_cast<Function>(o);
				output << utils::tab(indent) << type_of(f->type) << " " << name_guard << f->name << "(";
				
				VRef::iterator it = o->children.begin(); 
				
				while(it != o->children.end()) {
					if ((*it)->getType() == Component::ARGUMENT) {
						boost::shared_ptr<Argument> a = boost::dynamic_pointer_cast<Argument>(*it);
						output << type_of(a->type) << " " << (*it)->name;
						if (++it != o->children.end()) {
							output << ", ";
						}
					}
					else
						++it;
				}
				output << ");" << std::endl;
				break;
			}
		}
	}
	
	String type_of(Type t) {
		p_Component o = t.type;
		String r = "";
		VRef parents = o->parents();
		for (VRef::reverse_iterator it = parents.rbegin(); it != parents.rend(); ++it) {
			r += name_guard + (*it)->name + "::";
			if (*it == current_namespace)
				r = "";
		}
		r += name_guard + o->name;
		switch (t.method) {
			case Type::POINTER:
			{
				r = private_guard + "Pointer<" + r + ">";
				break;
			}
			case Type::REFERENCE:
			{
				r += "&";
				break;
			}
		}
		return r;
	}
	
	void define(p_Component o) {
		switch (o->getType()) {
			case Component::FUNCTION:
			{
				namespace_set(o);
				boost::shared_ptr<Function> f = boost::dynamic_pointer_cast<Function>(o);
				String class_space = "";
				if (o->parent->getType() == Component::CLASS) {
					class_space = name_guard + o->parent->name + "::";
				}
				output << std::endl << utils::tab(indent) << type_of(f->type) << " " << class_space << name_guard << f->name << "(";
				
				VRef::iterator it = o->children.begin(); 
				
				while(it != o->children.end()) {
					if ((*it)->getType() == Component::ARGUMENT) {
						boost::shared_ptr<Argument> a = boost::dynamic_pointer_cast<Argument>(*it);
						output << type_of(a->type) << " " << (*it)->name;
						if (++it != o->children.end()) {
							output << ", ";
						}
					}
					else
						++it;
				}
				output << ") {" << std::endl;
				// Body
				indent++;
				for (it = o->children.begin(); it != o->children.end(); ++it) {
					if ((*it)->getType() == Component::BLOCK) {
						output << utils::tab(indent) << "// Body" << std::endl;
					}
				}
				
				output << std::endl;
				indent--;
				output << utils::tab(indent) << "}" << std::endl;
				break;
			}
		}
	}
	
	void define_start(p_Component o) {
		switch (o->getType()) {
			case Component::CLASS:
			{
				namespace_set(o);
				output << std::endl << utils::tab(indent++) << name_guard << "class " << o->name << " {" << std::endl;
				break;
			}
		}
	}
	
	void define_end(p_Component o) {
		switch (o->getType()) {
			case Component::CLASS:
			{
				output << utils::tab(--indent) << "};" << std::endl;
				break;
			}
		}
	}
	
};

#endif