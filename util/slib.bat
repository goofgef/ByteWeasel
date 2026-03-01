@echo off
cd /d "%~dp0\.."

cmake -S cmake/static -B build/static
cmake --build build/static
pause