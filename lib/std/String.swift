#no-cpp

class String {
	/*
		String class;
		...
	*/
	
	String(char* value);
	
	String replace(Regex match, String value, bool all = false);
	String find(Regex match);
	
	char operator [int i];
}