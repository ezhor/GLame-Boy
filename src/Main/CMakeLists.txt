project(Main)

add_executable(${PROJECT_NAME} 
    src/main.cpp
)

set_target_properties(Main PROPERTIES OUTPUT_NAME "GLame Boy")

target_include_directories(${PROJECT_NAME}
    PRIVATE ./src
)

target_link_libraries(${PROJECT_NAME} PUBLIC Emulator)