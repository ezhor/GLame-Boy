git submodule init
git submodule update

cmake -S . -B ./build -DTESTS=True
cmake --build ./build

.\build\src\Main\Debug\Main.exe
pause