#include "Cucumber.h"

Cucumber::Cucumber(const glm::vec3& position) : Entity(), Controllable()
{
	this->position = position;
	this->models.push_back(Model("Egg 1/kart_YS_b.obj", position));
	this->camera = new OrbitalCamera(position);
}

Cucumber::~Cucumber()
{
}

void Cucumber::update(float deltaTime)
{
}

void Cucumber::mouseMoved(float deltaX, float deltaY)
{
	this->camera->mouseMoved(deltaX, deltaY);
}

void Cucumber::pollKeyboard(GLFWwindow* window)
{
	this->moveSpeed = 1.0f;
	this->strafeSpeed = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->moveSpeed += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->strafeSpeed -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->moveSpeed -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->strafeSpeed += 1.0f;
	}
}
