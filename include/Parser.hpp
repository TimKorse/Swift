
#include <fstream>

#include "default.hpp"

#include "Scanner.hpp"
#include "Component.hpp"
#include "Error.hpp"
#include "Token.hpp"
#include "Type.hpp"

#include "includes.hpp"

void debug(int i);

class Parser
{
	enum Access {
		PRIVATE,
		PUBLIC
	};
	
	Access access;
public:
	p_Component context;
	p_Component base; // Total base context for imports.
	p_Component object;
	
	Scanner scanner;
	fs::path source;
	
	Parser(fs::path s, p_Component context_, const String& name = "") throw (p_Error) : context(context_) {
		base = context;
		while (base->parent != NULL) {
			base = base->parent;
		}

		if (base->getType() != Component::BASE) {
			throw p_Error(new Error());
		}	
		
		if (fs::is_directory(s)) {
			s /= s.filename();
			s.replace_extension(".cx");
			std::cout << s << std::endl;
		} 
		scanner = Scanner(s);
		source = s;
		
		object = p_Component(new Temp(name));
		context->create(object);
	}	
	
	~Parser() {

	}
		
	void parse() throw (p_Error) {
		while (!scanner.eof()) {
			switch (scanner.read())
			{
				case Token::WORD:
				{
					if (scanner.get() == "import")
					{
						parse_import();
					}
					else if (scanner.get() == "public")
					{
						access = PUBLIC;
					}
					else if (scanner.get() == "private")
					{
						access = PRIVATE;
					}
					else if (scanner.get() == "class")
					{
						scanner.expect(Token::WORD);
						parse_component(p_Component(new Class(scanner.get(), source)));
					}
					else if (scanner.get() == "interface")
					{
						//object = new Inteface();
					}
					else if (scanner.get() == "module")
					{
						scanner.expect(Token::WORD);
						parse_component(p_Component(new Module(scanner.get(), source)));
					}
					
					break;
				}
				
				case Token::EOS:
				{
					
					break;
				}
				
				case Token::DIRECTIVE:
				{
					// Not yet implemented..
					break;
				}
				
				default:
					throw p_Error(new UnexpectedToken(scanner.get()));
			}
		}
	}
	
	void parse_component(p_Component temp) {
		if (object->getType() != Component::TEMP)
		{
			throw p_Error(new MultipleComponentDefinition(temp->name));
		}
		if (object->name != temp->name) {
			//throw ComponentMismatch();
			temp->name = object->name;
		}
		
		
		boost::shared_ptr<Temp> t = boost::dynamic_pointer_cast<Temp>(object);
		for (std::vector<p_Component>::iterator it = t->references.begin(); it != t->references.end(); ++it) {
			boost::dynamic_pointer_cast<Reference>(*it)->ref = temp;
		}		
		context->set(temp);
		object = temp;
		parse_definition_block();
	}	
	
	p_Component parse_import_sub(p_Component i, bool with_children = true) throw (p_Error) {
		scanner.expect(Token::WORD);
		try {
			p_Component o = i->find(scanner.get(), with_children);
			parse_import_refer(o);
			return o;
		}
		catch (p_Error e) {

			// <sub> is not defined. Import it!
			boost::shared_ptr<Base> pbase = boost::dynamic_pointer_cast<Base>(base);
			
			fs::path leaf = i->path / scanner.get();
			
			for (std::vector<fs::path>::iterator it = pbase->begin(); it != pbase->end(); it++) {
				fs::path t = *it / leaf;
			
				if (fs::exists(t)) {
					p_Component o = i->create(p_Component(new Module(scanner.get(), t)));

					parse_import_refer(o);
					return o;
				}
				
			
				t += ".cx";
			
				if (fs::exists(t)) {
					Parser parser(t, i, scanner.get());
					try
					{
						parser.parse();
					}
					catch (p_Error e)
					{
						scanner = parser.scanner;
						throw e;
					}
					
					p_Component o = i->find(scanner.get(), with_children);

					// create Reference
					parse_import_refer(o);
										
					return o;
				}
			}

			throw p_Error(new CannotImport(leaf));
		}
	}
	
	void parse_import_refer(p_Component o) {
		p_Component r;
		try {
			r = object->create(p_Component(new Reference(o)));
		} catch(...) {}
		
		if (o->getType() == Component::TEMP)
			(boost::dynamic_pointer_cast<Temp>(o))->references.push_back(r->shared_from_this());
	}
	
	void parse_import() throw (p_Error) {
		
		p_Component i = parse_import_sub(base, true);
		
		
		while (scanner.check('.'))
		{
			i = parse_import_sub(i, false);
		}

		scanner.expect(Token::SEMI);
	}
	
	void parse_definition_block() throw (p_Error) {
		scanner.expect(Token::BRACE_OPEN);
		while (!scanner.check('}')) {
			parse_definition();
		}
	}
	
	String parse_block() throw (p_Error) {
		scanner.expect(Token::BRACE_OPEN);
		int indent = 1;
		while (true) {
			scanner.skip();
			switch (scanner.peek()) {
				case '{':
					indent++;
					scanner.next();
					break;
				case '}':
					if (!--indent) { 
						String result = scanner.get();
						scanner.next();
						return result;
					}
					break;
				case '"': // String literal
					scanner.next();
					while (scanner.peek() != '"') {
						if (scanner.peek() == '\\') {
							scanner.next();
							scanner.next();
						}
						scanner.next();
					}
					scanner.next();
					break;
				case '\'': // Char literal
					scanner.next();
					scanner.next();
					scanner.next();
					break;
				default:
					scanner.next();
			}
		}
	}
	
	void parse_definition() throw (p_Error) {
		// TYPE
		Type type = parse_type();
		
		// NAME
		scanner.expect(Token::WORD);
		String name = scanner.get();
		
		if (scanner.check('(')) {
			// Function
			p_Component f = object->create(p_Component(new Function(name, type)));
			
			if (!scanner.check(')')) {
				do {
				
					Type type = parse_type();
		
					scanner.expect(Token::WORD);
					String name = scanner.get();
		
					f->create(p_Component(new Argument(name, type)));
				} while (scanner.check(','));
			}
			scanner.check(')');
			
			if (!scanner.check(';')) {
				f->create(p_Component(new Block(parse_block())));	
			}
			
		} else {
			// Variable
			object->create(p_Component(new Variable(name, type)));
			scanner.expect(Token::SEMI);
		}
	}
	
	
	p_Component parse_type_sub(p_Component i, bool with_parents = true) throw (p_Error) {
		scanner.expect(Token::WORD);
		p_Component type = i->resolve()->find(scanner.get(), with_parents);
		Component::Kind t = type->getType();
		//if (t != Object::CLASS && t != OBJECT::PRIMITIVE &&
		// throw ErrorRef(new TypeExpected());
		return type;
	}
	
	Type parse_type() throw (p_Error) {
		p_Component i = parse_type_sub(object, true);
		while (scanner.check('.'))
		{
			i = parse_type_sub(i, false);
		}
		Type type(i);
		if (scanner.check('*'))
		{
			type.method = Type::POINTER;
		}
		else if (scanner.check('&')) {
			type.method = Type::REFERENCE;
		}
		else
		{
			type.method = Type::PLAIN;
		}
		return type;
	}
};