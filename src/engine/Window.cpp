#include "Window.h"
#include <string>

void Window::init(int major, int minor) {
  glfwSetErrorCallback([](int error, const char* description) {
    throw "GLFW Error " + std::to_string(error) + ":\n" + description + "\n";
  });

  if(!glfwInit()) throw "Failed to start GLFW\n";

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  
  if (major >= 3) {
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
  }
// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
// #endif
  
  glfwWindowHint(GLFW_RESIZABLE, 1);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
}

Window::Window(const char* name, int w, int h, int ma, int mi) {
  init(ma, mi);
  
  title = name;

  handle = glfwCreateWindow( w, h, title, NULL, NULL );
  
  if (!handle) {
    glfwTerminate();
    throw "Failed to create window\n";
  }
  makeCurrent();
}

Window::Window(const char* name, int w, int h) {
  title = name;

  handle = glfwCreateWindow( w, h, title, NULL, NULL );
  
  if (!handle) {
    glfwTerminate();
    throw "Failed to create window\n";
  }
  makeCurrent();
}

Window::~Window() 
{

}

bool Window::shouldClose() 
{
	return glfwWindowShouldClose(handle);
}

void Window::makeClose() 
{
  glfwSetWindowShouldClose(handle, GLFW_TRUE);
}


void Window::swapInterval(int i) 
{
  glfwSwapInterval(i);
}

void Window::update() 
{
	glfwSwapBuffers(handle);
	glfwPollEvents();	
}

void Window::swap() 
{
  glfwSwapBuffers(handle);
}

void Window::poll() 
{
  glfwPollEvents(); 
}

void Window::makeCurrent() 
{
  glfwMakeContextCurrent(handle);
}

void Window::terminate() 
{
  glfwTerminate();
}

void Window::destroy() 
{
  glfwDestroyWindow(handle);
}

GLFWwindow *Window::getHandle() 
{
  return handle;
}

void Window::onKey(GLFWkeyfun func) 
{
  glfwSetKeyCallback(handle, func);
}

void Window::onResize(GLFWframebuffersizefun func) 
{
  glfwSetFramebufferSizeCallback(handle, func);
}

void Window::setTitle(const char* new_title) 
{
  glfwSetWindowTitle(handle, new_title);
}

bool Window::keyPressed(int key) 
{
  return glfwGetKey(handle, key) == GLFW_PRESS;
}

bool Window::keyReleased(int key) 
{
  return glfwGetKey(handle, key) == GLFW_RELEASE;
}

bool Window::btnPressed(int btn) 
{
  return glfwGetMouseButton(handle, btn) == GLFW_PRESS;
}

bool Window::btnReleased(int btn) 
{
  return glfwGetMouseButton(handle, btn) == GLFW_RELEASE;
}

void Window::getMouseChange(double & mouseX, double & mouseY) 
{
  getMousePosition(mouseX, mouseY);
  int w, h;
  getWindowSize(w, h);

  mouseY = (float)(mouseY - ((float)h / 4)) / h;
  mouseX = (float)(mouseX - ((float)w / 4)) / w;
}

void Window::getMousePosition(double &mouseX, double &mouseY) 
{
  glfwGetCursorPos(handle, &mouseX, &mouseY);
}

void Window::getWindowSize(int &w, int &h) 
{
  glfwGetFramebufferSize(handle, &w, &h);
}

void Window::setWindowSize(int w, int h) 
{
  glfwSetWindowSize(handle, w, h);
}

void Window::getWindowPosition(int &x, int &y) 
{
  glfwGetWindowPos(handle, &x, &y);
}

void Window::setWindowPosition(int x, int y) 
{
  glfwSetWindowPos(handle, x, y);
}

void Window::centerMouse() 
{
  int x, y;
  getWindowPosition(x, y);
  
  int w, h;
  getWindowSize(w, h);

  glfwSetCursorPos(handle, (float)w/4, (float)h/4);
}

void Window::hideMouse() 
{
  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::showMouse() 
{
  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
  
void Window::cursorCrosshair()
{
  if (crosshair == NULL)
  {
    crosshair = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
  }
  glfwSetCursor(handle, crosshair);
}

void Window::cursorNormal()
{
  if (crosshair != NULL)
  {
    glfwSetCursor(handle, NULL);
    crosshair = NULL;
  }
}

bool Window::didReleaseRightClick()
{
  if (already_right_clicked && btnReleased(GLFW_MOUSE_BUTTON_RIGHT))
  {
    if (already_released_right_click) 
    {
      already_released_right_click = false;
    }
    else {
      already_released_right_click = true;
      return true;
    }
  }
  didRightClick();
  return false;
}

bool Window::didRightClick()
{
  if (already_right_clicked && btnReleased(GLFW_MOUSE_BUTTON_RIGHT)) 
  {
    already_right_clicked = false;
  }
  else if (!already_right_clicked && btnPressed(GLFW_MOUSE_BUTTON_RIGHT))
  {
    already_right_clicked = true;
    already_released_right_click = false;
    return true;
  }

  return false;
}

bool Window::didReleaseLeftClick()
{
  if (already_left_clicked && btnReleased(GLFW_MOUSE_BUTTON_LEFT))
  {
    if (already_released_left_click) 
    {
      already_released_left_click = false;
    }
    else {
      already_released_left_click = true;
      return true;
    }
  }
  didLeftClick();
  return false;
}

bool Window::didLeftClick()
{
  if (already_left_clicked && btnReleased(GLFW_MOUSE_BUTTON_LEFT)) 
  {
    already_left_clicked = false;
  }
  else if (!already_left_clicked && btnPressed(GLFW_MOUSE_BUTTON_LEFT))
  {
    already_left_clicked = true;
    already_released_left_click = false;
    return true;
  }

  return false;
}
