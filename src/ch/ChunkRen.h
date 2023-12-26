#ifndef CHUNK_REN_CLASS_H
#define CHUNK_REN_CLASS_H

#include "../engine/Logic.h"
#include "../engine/TextureArray.h"
#include "../engine/Program.h"

#include "Chunk.h"
#include "Camera.h"

class ChunkRen : public Logic {
public:
	ChunkRen(int rad_xz, int rad_y, int ch_size, bool hollow);
	~ChunkRen();

protected:
	void init() override;
	void render(int, int) override;
	void update(int, int) override;
	void input() override;

private:
	const int rad_xz, rad_y, ch_size;
	const bool hollow;

  Camera camera;
  Program* program;
	TextureArray* textures;
  glm::mat4 projection{1.0f};
  
	std::vector<Chunk*> chunks;
};

#endif