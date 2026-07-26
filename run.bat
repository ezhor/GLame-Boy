git submodule init
git submodule update

cmake -S . -B ./build
cmake --build ./build

".\build\src\Main\Debug\GLame Boy.exe" .\test-roms\blargg\individual\01-special.gb
pause