#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {

public:
	static void init(int major, int minor);
	static void terminate();

	Window(const char* name, int width, int height);
	Window(const char* name, int width, int height, int major, int minor);
	~Window();
	
	
	bool shouldClose();
	void makeClose();

	void update();
	void swap();
	void swapInterval(int);
	void poll();
	void destroy();

	GLFWwindow *getHandle();

	void makeCurrent();

	bool keyPressed(int key);
	bool keyReleased(int key);
	bool btnPressed(int btn);
	bool btnReleased(int btn);

	void hideMouse();
	void showMouse();
	
	void cursorCrosshair();
	void cursorNormal();

	void centerMouse();

	void getMouseChange(double &, double &);
	void getMousePosition(double &, double &);
	void getWindowSize(int &, int &);
	void setWindowSize(int, int);
	void getWindowPosition(int &, int &);
	void setWindowPosition(int, int);
	
	void onKey(GLFWkeyfun);
	void onResize(GLFWframebuffersizefun);
	
	void setTitle(const char*);
	
	bool didLeftClick();
	bool didReleaseLeftClick();
	
	bool didRightClick();
	bool didReleaseRightClick();

private:

	GLFWcursor* crosshair = NULL;
	const char* title;
	int width, height;
	GLFWwindow* handle;
	
	bool already_left_clicked = false;
	bool already_released_left_click = false;
	
	bool already_right_clicked = false;
	bool already_released_right_click = false;

};