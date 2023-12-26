#pragma once

#include <glm/glm.hpp>

class Camera {

public:
	glm::mat4 matrix;
	Camera();
	void rotate(float x, float y);
	void translate(double x, double y, double z);
	void moveUp(float by);
	void moveDown(float by);
	void moveLeft(float by);
	void moveRight(float by);
	void moveForward(float by);
	void moveBackward(float by);
	
	void updateMatrix();

	glm::vec3 position;
	glm::vec3 orientation;

	const glm::vec3 UP;
	const glm::vec3 RIGHT;
	const glm::vec3 FRONT;

private:

	float oldRot;

	void holdOrientation();
	void resetOrientation();

};