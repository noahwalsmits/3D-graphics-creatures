#include "OrbitalCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrbitalCamera::OrbitalCamera(glm::vec3& target) : target(target), Camera()
{
	this->updateViewingAngle();
}

glm::mat4 OrbitalCamera::getViewMatrix() const
{
	return glm::lookAt(this->position, this->target, this->worldUp);
}

void OrbitalCamera::mouseMoved(float deltaX, float deltaY)
{
	this->yaw -= deltaX * this->MOUSE_SENSITIVITY;
	this->yaw = remainderf(this->yaw, 360.0f);

	this->pitch -= deltaY * this->MOUSE_SENSITIVITY;
	if (pitch > this->MAX_PITCH)
	{
		pitch = this->MAX_PITCH;
	}
	if (pitch < this->MIN_PITCH)
	{
		pitch = this->MIN_PITCH;
	}

	this->updateViewingAngle();
}

void OrbitalCamera::pollKeyboard(GLFWwindow* window)
{

}

void OrbitalCamera::updateViewingAngle()
{
	this->position.x = this->target.x + this->distance * cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
	this->position.y = this->target.y + this->distance * sin(glm::radians(this->pitch));
	this->position.z = this->target.z + this->distance * cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
}
