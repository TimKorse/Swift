#ifndef HG_OBJECT_BASE
#define HG_OBJECT_BASE

#include "../Component.hpp"
#include "../utils.hpp"

#include <vector>
#include <stack>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

class Base : public Component {
	std::vector<boost::filesystem::path> paths;
	std::stack<boost::shared_ptr<Scanner>> scanners;
	
public:
	void addScanner(Scanner* scanner) {
		scanners.push(boost::shared_ptr<Scanner>(scanner));
	}
	
	void popScanner() {
		scanners.pop();
	}
	
	boost::shared_ptr<Scanner> getScanner() {
		return scanners.top();
	}

	Base() : Component::Component("Base") {
	}
	
	void add(boost::filesystem::path path) {
		paths.insert(paths.begin(), path);
	}
	
	std::vector<boost::filesystem::path>::iterator begin() {
		return paths.begin();
	}
	
	std::vector<boost::filesystem::path>::iterator end() {
		return paths.end();
	}
	
	virtual String representate(int indent = 0, bool children = true) {
		String result = utils::tab(indent) + "base: ";
		if (children) {
			result += "{\n";
			result += Component::representate_children(indent, true);
			result += "}\n";
		}
		return result;
	}
	
	virtual Kind getType() {
		return BASE;
	}
};

#endif