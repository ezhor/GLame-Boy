project(Emulator)

add_library(${PROJECT_NAME}
	./include/Emulator.h
	./src/Emulator.cpp
	./include/Renderer.h
	./src/Renderer.cpp
	./include/Cpu.h
	./src/Cpu.cpp
	./include/Ppu.h
	./src/Ppu.cpp
	./include/Bus.h
	./src/Bus.cpp
	./include/Registers.h
	./src/Registers.cpp
	./include/Common.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC dependencies/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
