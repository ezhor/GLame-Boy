cmake_minimum_required(VERSION 3.17)
project(GLameBoy)

# C++ 17 for inline variables
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# Dependencies
add_subdirectory(dependencies/glad/)
add_subdirectory(dependencies/GLFW)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME}
	./src/GLameBoy/main.cpp
	./src/GLameBoy/Emulator.h
	./src/GLameBoy/Emulator.cpp
	./src/GLameBoy/Renderer.h
	./src/GLameBoy/Renderer.cpp
	./src/GLameBoy/Cpu.h
	./src/GLameBoy/Cpu.cpp
	./src/GLameBoy/Ppu.h
	./src/GLameBoy/Ppu.cpp
	./src/GLameBoy/Bus.h
	./src/GLameBoy/Bus.cpp
	./src/GLameBoy/Registers.h
	./src/GLameBoy/Registers.cpp
	./src/GLameBoy/Common.h
)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PUBLIC dependencies/GLFW/include)
target_include_directories(${PROJECT_NAME} PUBLIC dependencies/glad/include)