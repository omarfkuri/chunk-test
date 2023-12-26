#include "ChunkRen.h"
#include "Chunk.h"

#include <fstream>
#include <string>
#include <sys/stat.h>

#include <glm/gtc/type_ptr.hpp>

ChunkRen::ChunkRen(int rad_xz, int rad_y, int ch_size, bool hollow):
Logic("Chunk Render", 1200, 900),
rad_xz(rad_xz),
rad_y(rad_y),
ch_size(ch_size),
hollow(hollow)
{
	
}


bool exists(std::string path) {
  struct stat buffer;
  return stat (path.c_str(), &buffer) == 0;
}

std::string read(std::string path) {
  if (!exists(path)) {
    throw "File '" + path + "' does not exist.\n";
  }
  std::string line, text;
  std::ifstream file(path);
  
  while(std::getline(file, line)) 
    text += line + "\n";
  
  return text;
}

void ChunkRen::init()
{
  program = new Program(
  	read("./shader.vert").c_str(), 
  	read("./shader.frag").c_str()
  );

	textures = new TextureArray(32, 32);

	textures->add("rock", "./rock.png");

	for (int cX = 0; cX < rad_xz; cX++) {
		for (int cY = 0; cY < rad_y; cY++) {
			for (int cZ = 0; cZ < rad_xz; cZ++) {
				chunks.push_back(new Chunk(cX, cY, cZ, ch_size, hollow));
			}
		}
	}
}

void ChunkRen::update(int w, int h)
{
	projection = glm::perspective(70.f, (float)w/h, 0.1f, 1000.f);
	camera.updateMatrix();
}

void ChunkRen::render(int, int)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	
	glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	program->use();
	program->setMat4f("projection", glm::value_ptr(projection));
	program->setMat4f("view", glm::value_ptr(camera.matrix));

	for (auto chunk: chunks)
	{
		chunk->render(*program);
	}
	
}

void ChunkRen::input()
{

	static const float SENSITIVITY = 100.f;
	static const float SPEED = 0.1f;

	float by = SPEED;

	if (window.keyPressed(GLFW_KEY_SPACE))
	{
		camera.moveUp(by);
	}
	else if (window.keyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		camera.moveDown(by);
	}

	if (window.keyPressed(GLFW_KEY_A))
	{
		camera.moveLeft(by);
	}
	else if (window.keyPressed(GLFW_KEY_D))
	{
		camera.moveRight(by);
	}

	if (window.keyPressed(GLFW_KEY_W))
	{
		camera.moveForward(by);
	}
	else if (window.keyPressed(GLFW_KEY_S))
	{
		camera.moveBackward(by);
	}

	window.hideMouse();

	double cx, cy;
	window.getMouseChange(cy, cx);
	window.centerMouse();

	cx *= SENSITIVITY;
	cy *= SENSITIVITY;

	camera.rotate(cx, cy);
}

ChunkRen::~ChunkRen()
{
	for (auto ch: chunks)
	{
		delete ch;
	}

	delete program;
	delete textures;
}
