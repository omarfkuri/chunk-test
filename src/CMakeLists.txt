add_subdirectory(ch)
add_subdirectory(engine)

add_library(src main.cpp)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(src PUBLIC 
	engine
	
	ch

	glfw
	GLEW::GLEW 
	${GLUT_LIBRARY}
)