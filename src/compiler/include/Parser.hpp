#ifndef HG_PARSER
#define HG_PARSER

#include "default.hpp"

class Scanner;

class Parser {
	Scanner scanner;
public:
	Parser(Path path);
	
	void parse_main() throw (p_Error);
	void parse_import() throw (p_Error);
	void parse_import_sub() throw (p_Error);
	void parse_main() throw (p_Error);
	
};

#endif //HG_PARSER