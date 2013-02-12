@echo off
REM Copyright (©) 2010-2011 sar3th
set PATH=%~dp0\..\c++\compiler\bin;%PATH%

REM title MinGW Portable Command Prompt
REM cd /d "%~dp0"

g++ main.cpp -g ^
-std=c++0x -static-libgcc -static-libstdc++ ^
src/Scanner.cpp ^
src/Object.cpp ^
-I"../c++/include" ^
-L"../c++/lib" ^
-l"boost_filesystem-mgw46-mt-1_52" ^
-l"boost_system-mgw46-mt-1_52" ^
-o test.exe -W
pause