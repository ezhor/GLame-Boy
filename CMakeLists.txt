cmake_minimum_required(VERSION 3.17)
project(GLameBoy)

# C++ 17 for inline variables
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


add_executable(${PROJECT_NAME} ./src/GLameBoy ./src/GLameBoy/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./src/GLameBoy)