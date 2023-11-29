cmake_minimum_required(VERSION 3.17)
project(GLameBoy)

# C++ 17 for inline variables
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_subdirectory(dependencies/GLFW)
target_include_directories(GLAD, PUBLIC dependencies/GLFW)

add_executable(${PROJECT_NAME} ./src/GLameBoy ./src/GLameBoy/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC dependencies/GLFW)
target_link_libraries(${PROJECT_NAME} PUBLIC dependencies/GLAD)