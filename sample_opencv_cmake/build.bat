@echo off
cd .\build
cmake -G "MinGW Makefiles" .. > TriffleInfo
make
