project(Tests)

add_executable(${PROJECT_NAME}
        include/TestUtils.h
        src/TestUtils.cpp
        src/EmulatorTests.cpp
        src/InstructionsTests.cpp
        src/InstructionsTests_POP.cpp
        src/InstructionsTests_PUSH.cpp
        src/InstructionsTests_CALL.cpp
        src/InstructionsTests_RET.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ../Emulator/include)
target_include_directories(${PROJECT_NAME} PRIVATE ../../dependencies/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(${PROJECT_NAME} PUBLIC Emulator)
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})
