@echo off
md .\build
cd .\build
cmake -G "MinGW Makefiles" ..
make
