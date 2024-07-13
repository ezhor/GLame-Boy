git submodule init
git submodule update

RMDIR /S /Q "./build"

cmake -S . -B ./build -DTESTS=True
cmake --build ./build

.\build\src\Main\Debug\Main.exe
pause