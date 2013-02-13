@echo off
set PATH=C:/Users/Tim/Desktop/Swift/c++/compiler/bin;%PATH%


g++ -g -std=c++0x -static-libgcc -static-libstdc++ ^
src/main.cpp ^
src/Scanner.cpp ^
src/Component.cpp ^
-I"C:/Users/Tim/Desktop/Swift/c++/include" ^
-L"C:/Users/Tim/Desktop/Swift/c++/lib" ^
-I"include" ^
-l"boost_filesystem-mgw46-mt-1_52" ^
-l"boost_system-mgw46-mt-1_52" ^
-o "bin/compiler.exe" -W
pause