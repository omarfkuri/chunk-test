#include "TextureArray.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <iostream>

TextureArray::TextureArray(int w, int h):
image_size(w, h)
{
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + textureSlotIndex);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image_size.x, image_size.y, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unitID = textureSlotIndex;
	textureSlotIndex++;
}

int TextureArray::get(std::string id)
{
	if (textures.find(id) == textures.end())
	{
		throw "TextureArray member " + id + " does not exist";
	}
	return textures.at(id);
}

void TextureArray::add(std::string id, std::string filePath)
{
	if (textures.find(id) != textures.end())
	{
		throw "TextureArray member " + id + " already exists";
	}
	GLint width, height, nrChannels;
  unsigned char *bytes = stbi_load(filePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha); // Loading as rgb_alpha so transparent pixels are transparent

  stbi_set_flip_vertically_on_load(false);
  if (bytes)
  {
  	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, image_index, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, bytes);  
  	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
  }
  else
  {
  	throw "Failed to load texture " + filePath;
  }
  
	stbi_image_free(bytes);

  textures.insert({id, image_index});
  image_index++;
}

void TextureArray::bind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void TextureArray::unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
	glDeleteTextures(1, &textureID);
}
