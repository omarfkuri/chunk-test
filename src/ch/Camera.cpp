#include "Camera.h"
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(): 
orientation(0, 0, 1), 
UP(0, 1, 0),
RIGHT(1, 0, 0),
FRONT(0, 0, -1)
{
	updateMatrix();
}

void Camera::rotate(float x, float y)
{
	glm::vec3 new_orientation = glm::rotate(orientation, -glm::radians(x), glm::normalize(glm::cross(orientation, UP)));
	if (abs(glm::angle(new_orientation, UP) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
		orientation = new_orientation;
	}
	orientation = glm::rotate(orientation, -glm::radians(y), UP);
}

void Camera::translate(double x, double y, double z) 
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::moveUp(float by) 
{
	position += by * UP;
}

void Camera::moveDown(float by) 
{
	position -= by * UP;
}

void Camera::moveLeft(float by) 
{
	holdOrientation();
	position -= by * glm::normalize(glm::cross(orientation, UP));
	resetOrientation();
}

void Camera::moveRight(float by) 
{
	holdOrientation();
	position += by * glm::normalize(glm::cross(orientation, UP));
	resetOrientation();
}

void Camera::moveForward(float by) 
{
	holdOrientation();
	position += by * glm::normalize(orientation);
	resetOrientation();
}

void Camera::moveBackward(float by) 
{
	holdOrientation();
	position -= by * glm::normalize(orientation);
	resetOrientation();
}

void Camera::updateMatrix() 
{
	matrix = glm::lookAt(position, position + orientation, UP);
}

void Camera::holdOrientation() 
{
	oldRot = orientation.y;
	orientation.y = 0;
}

void Camera::resetOrientation() 
{
	orientation.y = oldRot;
}