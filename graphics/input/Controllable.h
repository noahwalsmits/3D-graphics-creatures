#pragma once
#include <GLFW/glfw3.h>

class Controllable
{
public:
	virtual ~Controllable() = default;

	virtual void mouseMoved(float deltaX, float deltaY) = 0;
	virtual void pollKeys(GLFWwindow* window, float deltaTime) = 0;
};

