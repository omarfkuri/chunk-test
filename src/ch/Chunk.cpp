#include "Chunk.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Chunk::Chunk(long _x, long _y, long _z, int ch_size, bool hollow):
x(_x),
y(_y),
z(_z),
chunk_size(ch_size),
tx(x * chunk_size),
ty(y * chunk_size),
tz(z * chunk_size)
{
  // creates VAO, VBO and EBO.
	start_buffers();

  // loads data to instance's indices and vertices vectors.
  // (This is the main source of trouble, as far as I can tell)
	load_data(hollow);

  // loads data from vectors to GPU
	load_buffers();
}

Chunk::~Chunk()
{
	clear_buffers();
}

void Chunk::render(const Program& program)
{
	program.setMat4f("model", glm::value_ptr(matrix));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vaoSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Chunk::start_buffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Chunk::load_data(bool hollow)
{
	int r = 0;

	for (int bX = 0; bX < chunk_size; bX++) {
		for (int bY = 0; bY < chunk_size; bY++) {
			for (int bZ = 0; bZ < chunk_size;   bZ++) 
			{
				if (!hollow || bX == 0 || bY == 0 || bZ == 0 || bX == chunk_size-1 || bY == chunk_size-1 || bZ == chunk_size-1)
				{
					load_data_for(bX, bY, bZ, r);
				}
			}
		}
	}
}

void Chunk::load_data_for(const long& bx, const long& by, const long& bz, int& r)
{
  // get the min and max x, y and z values for the position.
  // each value is the total of the chunk plus the current position
	float X0 = tx + bx, X1 = tx + bx + 1;
	float Y0 = ty + by, Y1 = ty + by + 1;
	float Z0 = tz + bz, Z1 = tz + bz + 1;

  // texture scale
	float t = 1;
	
  // Each face varies in normal and positions, so they are hard coded.

	// neg x
	{
		vertices.push_back(Vert{{X0, Y0, Z1}, {-1,-0,-0}, {0,t}, 0});
		vertices.push_back(Vert{{X0, Y1, Z1}, {-1,-0,-0}, {t,t}, 0});
		vertices.push_back(Vert{{X0, Y1, Z0}, {-1,-0,-0}, {t,0}, 0});
		vertices.push_back(Vert{{X0, Y0, Z0}, {-1,-0,-0}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}

	// pos x
	{
		vertices.push_back(Vert{{X1, Y0, Z0}, { 1,-0,-0}, {0,t}, 0});
		vertices.push_back(Vert{{X1, Y1, Z0}, { 1,-0,-0}, {t,t}, 0});
		vertices.push_back(Vert{{X1, Y1, Z1}, { 1,-0,-0}, {t,0}, 0});
		vertices.push_back(Vert{{X1, Y0, Z1}, { 1,-0,-0}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}

	// neg y
	{
		vertices.push_back(Vert{{X0, Y0, Z0}, {-0,-1,-0}, {0,t}, 0});
		vertices.push_back(Vert{{X1, Y0, Z0}, {-0,-1,-0}, {t,t}, 0});
		vertices.push_back(Vert{{X1, Y0, Z1}, {-0,-1,-0}, {t,0}, 0});
		vertices.push_back(Vert{{X0, Y0, Z1}, {-0,-1,-0}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}

	// pos y
	{
		vertices.push_back(Vert{{X1, Y1, Z1}, {-0,-1,-0}, {0,t}, 0});
		vertices.push_back(Vert{{X1, Y1, Z0}, {-0,-1,-0}, {t,t}, 0});
		vertices.push_back(Vert{{X0, Y1, Z0}, {-0,-1,-0}, {t,0}, 0});
		vertices.push_back(Vert{{X0, Y1, Z1}, {-0,-1,-0}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}

	// neg z
	{
		vertices.push_back(Vert{{X0, Y0, Z0}, {-0,-0,-1}, {0,t}, 0});
		vertices.push_back(Vert{{X0, Y1, Z0}, {-0,-0,-1}, {t,t}, 0});
		vertices.push_back(Vert{{X1, Y1, Z0}, {-0,-0,-1}, {t,0}, 0});
		vertices.push_back(Vert{{X1, Y0, Z0}, {-0,-0,-1}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}

	// pos z
	{
		vertices.push_back(Vert{{X1, Y0, Z1}, {-0,-0,-1}, {0,t}, 0});
		vertices.push_back(Vert{{X1, Y1, Z1}, {-0,-0,-1}, {t,t}, 0});
		vertices.push_back(Vert{{X0, Y1, Z1}, {-0,-0,-1}, {t,0}, 0});
		vertices.push_back(Vert{{X0, Y0, Z1}, {-0,-0,-1}, {0,0}, 0});

		indices.push_back({r, r+1, r+2});
		indices.push_back({r, r+2, r+3});
		r += 4;
	}
}

void Chunk::load_buffers()
{
	vaoSize = indices.size() * sizeof(glm::ivec3);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vaoSize, &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);

	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(offsetof(Vert, normal)));

	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(offsetof(Vert, texCoords)));

	glEnableVertexAttribArray(3);	
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(offsetof(Vert, texID)));

	glBindVertexArray(0);
}

void Chunk::clear_buffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}