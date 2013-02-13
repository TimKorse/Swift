#ifndef HG_DEFAULT
#define	HG_DEFAULT

#include <string>
#include <vector>
#include <stack>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

template <class T> class List : public std::vector<T> {};
template <class T> class Stack : public std::stack<T> {};
typedef std::string String;

class Component;
typedef boost::shared_ptr<Component> p_Component;

class Error;
typedef boost::shared_ptr<Error> p_Error;

class AST;
typedef boost::shared_ptr<AST> p_AST;

typedef p_Component Scope; // Exactly the same, but more obvious in most situations where scope is used.

namespace fs = boost::filesystem;

typedef fs::path Path;

#endif

