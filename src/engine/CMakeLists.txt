
add_library(engine 
	Window.cpp 
	Logic.cpp 
	Program.cpp
	TextureArray.cpp
	)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


target_link_libraries(engine PUBLIC 

	glfw
	GLEW::GLEW 
	${GLUT_LIBRARY}
)