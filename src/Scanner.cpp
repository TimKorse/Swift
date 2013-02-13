#include "Error.hpp"
#include "Token.hpp"

#include "Scanner.hpp"

#include <iostream>

#include "default.hpp"

Scanner::Scanner() {}

Scanner::Scanner(boost::filesystem::path p) : file(p), source(new std::ifstream(p.string().c_str())) {
	if (!eof() && source->good())
	{
		chr = (char) source->get();
	}
	current_pos = 1;
	current_line = 1;
	token_line = 1;
	token_pos = 1;
}

Scanner::~Scanner() {

}

void Scanner::skip() {
	while (peek() == '\t' || peek() == ' ' || peek() == '\n' || peek() == '\r' || peek() == '\f')
	{
		if (peek() == '\n')
		{
			current_line++;
			current_pos = 1;
		}
		next();
	}
}

bool Scanner::eof() {
	return source->eof();
}

void Scanner::clear() {
	current = "";
}

char Scanner::peek() {
	
	return chr;
}

bool Scanner::check(char c) {
	skip();
	if (peek() == c)
	{
		next();
		return true;
	}
	return false;
}


void Scanner::next() {
	current.push_back(peek());
	if (!eof() && source->good())
	{
		chr = (char) source->get();
		current_pos++;
	}
}

bool Scanner::between(char b, char e) {
	return (peek() >= b && peek() <= e);
}

bool Scanner::alpha() {
	return (between('a', 'z') || between('A', 'Z'));
}

bool Scanner::digit() {
	return between('0', '9');
}

Token Scanner::read() {
	skip();
	clear();
	token_pos = current_pos - 1;
	token_line = current_line;
	if (eof())
		return Token::EOS;
	if (alpha())
	{
		next();
		while (alpha() || peek() == '_' || digit())
		{
			next();
		}
		return Token::WORD;
	}
	else if (peek() == '.')
	{
		next();
		if (digit())
		{
			next();
			while (digit()) { next(); }
			return Token::DOUBLE;
		}
		else
		{
			return Token::POINT;
		}
	}
	else if (digit())
	{
		next();
		while (digit()) { next(); }
		if (peek() == '.')
		{
			next();
			while (digit()) { next(); }
			return Token::DOUBLE;
		}
		else
		{
			return Token::INT;
		}
	}
	else
	{
		switch (peek())
		{
			case ';':
				next();
				return Token::SEMI;
				break;
			case '{':
				next();
				return Token::BRACE_OPEN;
				break;
			case '}':
				next();
				return Token::BRACE_CLOSE;
				break;
			case '#':
				next();
				while (alpha() || peek() == '_' || peek() == '-' || digit())
				{
					next();
				}
				return Token::DIRECTIVE;
			default:
				next();
				return Token::NOONE;
		}
	}
	return Token::NOONE;
}

void Scanner::expect(Token token) throw (p_Error) {
	if (read() != token)
		throw p_Error(new ExpectedToken(token));
}

const String& Scanner::get() {
	return current;
}