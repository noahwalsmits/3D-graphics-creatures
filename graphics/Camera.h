#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	virtual ~Camera() = default;

	virtual glm::mat4 getViewMatrix() const = 0;
	virtual void mouseMoved(float deltaX, float deltaY) = 0;
	virtual void pollKeys(GLFWwindow* window, float deltaTime) = 0;
};

