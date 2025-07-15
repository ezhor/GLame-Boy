cmake_minimum_required(VERSION 3.17)
project(GLameBoy)
#set(TESTS True)

################################## C++ version ##################################

# C++ 17 for inline variables
# C++ 20 for string format
set(CMAKE_CXX_STANDARD 20)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

################################## Dependencies ##################################

# glad
add_subdirectory(dependencies/glad/)

# GLFW
include(FetchContent)
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Google Tests
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(dependencies/googletest)
include(GoogleTest)

################################## GLameBoy ##################################

add_subdirectory(src/Emulator)
add_subdirectory(src/Main)


################################## Tests ##################################

enable_testing()
add_subdirectory(src/Tests)
if(TESTS)
	add_custom_target(AllTests ALL
	COMMAND ${CMAKE_CTEST_COMMAND} ${CMAKE_BINARY_DIR}
	DEPENDS Tests
	COMMENT "Running tests"
	)
endif(TESTS)