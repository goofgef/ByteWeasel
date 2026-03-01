@echo off
cd /d "%~dp0\.."

cmake -S cmake/exe -B build/exe
cmake --build build/exe
pause