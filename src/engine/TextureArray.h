#ifndef TEXTUREARRAY_CLASS_H
#define TEXTUREARRAY_CLASS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

class TextureArray
{
public:
	TextureArray(int, int);
	~TextureArray();

	void add(std::string, std::string);
	int get(std::string);
	void bind();
	void unbind();
	
	GLuint unitID;
	GLuint textureID;

private:
	glm::vec2 image_size;
	std::map<std::string, int> textures;
	GLuint image_index = 0;
};

inline GLuint textureSlotIndex = 0;
#endif