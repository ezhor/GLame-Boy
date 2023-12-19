.\vcpkg.\vcpkg.exe install glad:x64-windows
.\vcpkg.\vcpkg.exe install glfw3:x64-windows

cmake -S . -B ./build
cmake --build ./build

.\build\Debug\GLameBoy.exe