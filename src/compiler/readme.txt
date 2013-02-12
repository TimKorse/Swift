To build the compiler:
	* you need GCC.
		- Windows:
			http://www.mingw.org/
			Download & install
		- Linux (Debian/Ubuntu):
			apt-get install gcc make linux-headers-$(uname -r)
		
		For other platforms, search the web...
			
	* you need the boost library:
		- Windows:
			http://www.boost.org/doc/libs/1_41_0/more/getting_started/windows.html
		  or prebuilt (be sure to get the same MinGW compiler!):
			http://nuwen.net/mingw.html
		- Unix:
			http://www.boost.org/doc/libs/1_41_0/more/getting_started/unix-variants.html
	
	* you need a build script:
		- Windows:
			See build.bat
		- Other:
			Convert build.bat to native script for your platform.
			
			