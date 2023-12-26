set (CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.13.4)

project(PlanetMatter)


add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} 
	src
	
	glfw
	GLEW::GLEW 
	glm::glm
)