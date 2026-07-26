git submodule init
git submodule update

cmake -S . -B ./build -DTESTS=True
cmake --build ./build --config Release

".\build\src\Main\Release\GLame Boy.exe" .\test-roms\blargg\individual\01-special.gb
pause