#ifndef HG_DEFAULT
#define HG_DEFAULT

#include <string>
#include <vector>
#include <stack>
/*
	Some ease for when this project will be converted to the Swift language.
*/


template <class T> class Vector : public std::vector<T> {};
template <class T> class Stack : public std::stack<T> {};
typedef std::string String;

#endif //HG_DEFAULT