#ifndef HG_PATH
#define HG_PATH

#include "default.hpp"

class Path {
	List<String> parts;
public:
	Path(const char* path);
	
	bool exists();
	
	/*
		Reads the file into a string
	*/
	String read();
	
	/*
		Representates the path as a string
	*/
	String repr();
	
	/*
		Concats two paths
	*/
	Path operator / (Path path);
};

#endif //HG_PATH