#ifndef HG_ERROR
#define HG_ERROR

#include <string>
#include <sstream>
#include <memory>

#include "Token.hpp"

#include "default.hpp"



class Error {
public:
	Error() {}
	virtual ~Error() {}
	virtual String what() {
		return "Not yet implemented";
	}
};



class UnexpectedEOF : public Error {
public:
	virtual String what() {
		return "Unexpected end of feed.";
	}
};

#include <boost/filesystem.hpp>

class CannotImport : public Error {
	boost::filesystem::path path;
public:
	CannotImport(boost::filesystem::path p) : path(p) {}
	
	virtual String what() {
		return "Can't find directory or file \"" + path.string() + "\"";
	}
};

class UnexpectedToken : public Error {
	String token;
public:
	UnexpectedToken(const String& t) : token(t) {} 
	
	virtual String what() {
		return String("Unexpected token \"") + token + String("\"");
	}
};

class ExpectedToken : public Error {
	String token;
public:
	ExpectedToken(const String& t) : token(t) {}
	ExpectedToken(Token t) {
		switch (t)
		{
			case Token::WORD:
			{
				token = "Word";
				break;
			}
			case Token::NOONE:
			{
				token = "None";
				break;
			}
			case Token::DOUBLE:
			{
				token = "Double";
				break;
			}
			default:
			{
				token = "Unknown: ";
				std::stringstream ss;//create a stringstream
				ss << (int)t;//add number to the stream
				token += ss.str();
			}
		}
	}
	virtual String what() {
		return token + " expected";
	}
};

class UndefinedObject : public Error {
	String name;
public:
	UndefinedObject(const String& n) : name(n) {}
	virtual String what() {
		return "Undefined reference to " + name;
	}
};

class MultipleDefinition : public Error {
	String name;
public:
	MultipleDefinition(const String& n) : name(n) {}
	virtual String what() {
		return "Multiple member definition with name " + name;
	}
};

class MultipleComponentDefinition : public Error {
	String name;
public:
	MultipleComponentDefinition(const String& n) : name(n) {}
	virtual String what() {
		return "Multiple component definition with name " + name;
	}
};

#endif //HG_ERROR