#ifndef LOGIC_CLASS_H
#define LOGIC_CLASS_H

#include <string>
#include <vector>

#include "Window.h"

#include <GL/glew.h>

class Logic {
public:
	Logic();
	Logic(std::string, int w, int h);
	virtual ~Logic();
	
	void run();

protected:
	
	void start();
	virtual void init() = 0;
	virtual void render(int, int) = 0;
	virtual void update(int, int) = 0;
	virtual void input() = 0;
	void end();

	Window window;

};

#endif