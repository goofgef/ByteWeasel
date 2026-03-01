@echo off
cd build
cmake ..
cmake --build .
set /p userpath=Return to path:
cd "%userpath%"
pause