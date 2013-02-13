#ifndef HG_SCANNER
#define HG_SCANNER

#include <fstream>
#include <string>
#include <memory>

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include "Token.hpp"
#include "Error.hpp"

class Scanner {
public:
	Scanner();
	Scanner(boost::filesystem::path p);
	~Scanner();
	
	char chr;
	unsigned int current_line, current_pos;
	unsigned int token_line, token_pos;
	boost::filesystem::path file;
	
	bool eof();
	Token read();
	void expect(Token token) throw (p_Error);
	const String& get();
	bool check(char c);
	// Meant for Scanner only, but will be provided for certain situations.
	void skip();
	void clear();
	char peek();
	void next();
	bool between(char b, char e);
	bool alpha();
	bool digit();
private: 
	
	boost::shared_ptr<std::ifstream> source;
	
	String current;
};

#endif //HG_SCANNER