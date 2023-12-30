git submodule init

cmake -S . -B ./build
cmake --build ./build

.\build\src\Main\Debug\Main.exe