@echo off
g++ main.cpp -g ^
-std=c++0x -static-libgcc -static-libstdc++ ^
src/Scanner.cpp ^
src/Object.cpp ^
-I "include" ^
-L "../c++/lib" ^
-l "boost_filesystem-mgw46-mt-1_52" ^
-l "boost_system-mgw46-mt-1_52" ^
-o "../../bin/compiler.exe" -W
pause