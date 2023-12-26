

add_library(
	ch 
	ChunkRen.cpp 
	Chunk.cpp 
	Camera.cpp
)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(ch PUBLIC 

	glfw
	GLEW::GLEW 
	${GLUT_LIBRARY}
)