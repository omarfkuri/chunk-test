#include "Logic.h"
#include <iostream>

static bool show_wires = false;
static bool quit = false;

Logic::Logic(std::string t, int w, int h):
window(t.c_str(), w, h, 3, 3)
{}

Logic::Logic():
Logic("Graph", 400, 400)
{}

void Logic::start()
{
  window.onKey([](GLFWwindow*, int k, int, int a, int){
  	if (a==GLFW_PRESS) return;

  	switch(k)
  	{
  	case GLFW_KEY_ESCAPE:
  		{
  			quit = true;
  			break;
  		}

  	case GLFW_KEY_L:
  		{
  			show_wires = !show_wires;
  			if (show_wires)
  			{
  				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  			}
  			else
  			{
  				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  			}
  			break;
  		}
  	}
  });

  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
  	std::cerr << "GLEW failed" << std::endl;
  	std::cerr << glewGetErrorString(err) << std::endl;
  	exit(0);
  }
}

void Logic::run()
{
	start();
	init();
	while (!quit)
  {
  	window.poll();
  	input();

  	int w, h;
  	window.getWindowSize(w, h);
  	glViewport(0, 0, w, h);

  	update(w, h);
  	render(w, h);

  	window.swap();
  	if (window.shouldClose())
  	{
  		break;
  	}
  	GLenum errorCode;
		if((errorCode = glGetError()) != GL_NO_ERROR)
		{
			std::string error;
			switch (errorCode)
			{
			case GL_INVALID_ENUM:                  
				error = "Invalid Enumeration"; 
			break;
			case GL_INVALID_VALUE:                 
				error = "Invalid Value"; 
			break;
			case GL_INVALID_OPERATION:             
				error = "Invalid Operation"; 
			break;
			case GL_STACK_OVERFLOW:                
				error = "Stack Overflow"; 
			break;
			case GL_STACK_UNDERFLOW:               
				error = "Stack Underflow"; 
			break;
			case GL_OUT_OF_MEMORY:                 
				error = "Out of Memory"; 
			break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: 
				error = "Invalid FrameBuffer Operation"; 
			break;
			}
			std::cerr << "GL Error: " << error << std::endl;
			break;
		}
	}
}

Logic::~Logic()
{
  window.destroy();

  Window::terminate();

}