#ifndef HG_TOKEN
#define HG_TOKEN

class Token {
public:
	enum Type {
		NOONE,
		WORD,
		DOUBLE,
		INT,
		STRING,
		SEMI,
		EOS,
		POINT,
		BRACE_OPEN,
		BRACE_CLOSE,
		DIRECTIVE
	} content;
	
	Token(Type value) : content(value) {}
	operator Type () {
		return content;
	}
};


#endif //HG_TOKEN