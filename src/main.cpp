#include <iostream>

#include "default.hpp"

#include "Parser.hpp"
#include "Component.hpp"

int main(int argc, char** argv)
{	
	if (argc == 1) return 1;
	
	Path entry(argv[1]);
	
	Base* base = new Base();
	
	// fs::canonical(fs::initial_path());
	Path exedir = boost::filesystem::system_complete(argv[0]).parent_path();
	//std::cout << exedir / "../lib" << std::endl;
	base->add(exedir / "../lib"); // Library folder
	
	if (fs::exists(entry)) {
		base->add(entry.parent_path());
	} else {
		if (fs::exists(fs::current_path() / entry))
		{
			entry = fs::current_path() / entry;
			base->add(entry.parent_path());
		}
		else 
		{
			std::cout << "Can't find entry " << entry << "" << std::endl; 
			return 1;
		}
	}
	
	Scope context(base);
	
	// Primairy types:
	context->create(Scope(new Primitive("void")));
	context->create(Scope(new Primitive("bool")));
	context->create(Scope(new Primitive("char")));
	context->create(Scope(new Primitive("byte"))); // unsigned char
	context->create(Scope(new Primitive("int")));
	context->create(Scope(new Primitive("uint")));
	context->create(Scope(new Primitive("short")));
	context->create(Scope(new Primitive("ushort")));
	context->create(Scope(new Primitive("float")));
	context->create(Scope(new Primitive("double")));
	
	Parser parser(entry, context, entry.stem().string());
	try
	{
		parser.parse();
		
		if (String(argv[2]) == "info") {
			std::cout << context->representate() << std::endl;
			std::cout << "Generating code..." << std::endl;
		}
		
		context->generate();
	}
	catch (p_Error e)
	{
		std::cout << context->representate() << std::endl << std::endl;
		
		std::cout << "An error occurred in: " << parser.scanner.file.filename() << std::endl << "on line " << parser.scanner.token_line << ", position " <<parser.scanner.token_pos << ":" << std::endl;

		std::cout << e->what() << std::endl;

	}
	catch (...)
	{
		std::cout << "Uknown exception occurred..." << std::endl;
	}
	return 0;
}