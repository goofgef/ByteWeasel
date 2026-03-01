@echo off
cd /d "%~dp0\.."

cmake -S cmake/shared -B build/shared
cmake --build build/shared
pause