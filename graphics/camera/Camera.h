#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	virtual ~Camera() = default;

	virtual glm::mat4 getViewMatrix() const = 0;
};

