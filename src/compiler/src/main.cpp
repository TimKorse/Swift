#include <iostream>

#include "default.hpp"
#include "AST.hpp"
#include "Path.hpp"
#include "Parser.hpp"
#include "info.hpp"


int main() {
	/* 
		Entry path
			Could be a module (directory) or a class.
			When there is no "static" main function found, the complete project is handled as a library.
	*/
	Path entry = "../../../examples/helloworld";
	
	// AST context for complete project
	p_AST ast = p_AST(new AST());
	
	Parser parser;
	Generator generator;
	Compiler compiler;
	
	try {
		// Parse Swift input
		parser = Parser(entry, ast);
		parser.parse();
		
		// Debug information: AST representation
		
		std::cout << std::endl << "AST representation: " << std::endl << ast.repr() << std::endl << std::endl;
		
		// Generate C++ output
		generator = Generator(ast);
		generator.generate();
		
		// Compile C++ units
		compiler = Compiler(ast);
		compiler.compile();
	}
	catch (p_Error error) {
		// Show scanner, parser, generator, printer or compiler error
		std::cout << "An error occurred in file:" << std::endl << info::file.repr() << std::endl << info::line << ':' << info::pos << ": " << error->repr() << std::endl;
	}
	
	return 0;
}