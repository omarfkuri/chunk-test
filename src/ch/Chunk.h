#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include <glm/glm.hpp>

#include "../engine/Program.h"

struct Vert {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	float texID;
};

class Chunk
{
public:
	Chunk(long x, long y, long z, int ch_size, bool hollow);
	~Chunk();

	const long x, y, z;
  const int chunk_size;
	const long tx, ty, tz;
  
  void render(const Program&);

private:
	GLuint VAO, VBO, EBO;
	
  long vaoSize;

  glm::mat4 matrix{1.0f};
  
	std::vector<glm::ivec3> indices;
	std::vector<Vert> vertices;

	void start_buffers();
	void clear_buffers();
	void load_data(bool);
	void load_data_for(const long&, const long&, const long&, int& r);
	void load_buffers();

};

#endif