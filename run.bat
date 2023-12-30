git submodule init
git submodule update

cmake -S . -B ./build
cmake --build ./build

.\build\src\Main\Debug\Main.exe