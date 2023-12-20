project(Tests)

add_executable(${PROJECT_NAME}
	TestUtils.h
	TestUtils.cpp
	InstructionsTests.cpp
	EmulatorTests.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC GLameBoy)
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})