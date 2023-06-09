#include "Cucumber.h"

Cucumber::Cucumber(const glm::vec3& position) : Entity(), Controllable()
{
	this->position = std::make_shared<glm::vec3>(position);
	this->rotation = std::make_shared<float>(0.0f);
	this->models.push_back(Model("cucumber/Cucumber.obj", position));
	this->camera = new OrbitalCamera(*this->position);

	for (Model& model : this->models)
	{
		model.position = this->position;
		model.rotationYaw = this->rotation;
	}
}

Cucumber::~Cucumber()
{
	delete this->camera;
}

void Cucumber::update(float deltaTime)
{
	//move forward/backward based on move input
	this->position->z += cos(glm::radians(*this->rotation)) * deltaTime * this->moveInput * MOVEMENT_SPEED;
	this->position->x += sin(glm::radians(*this->rotation)) * deltaTime * this->moveInput * MOVEMENT_SPEED;
	
	//turn 90 degreees and move forward/backward based on strafe input
	this->position->z += cos(glm::radians(*this->rotation - 90.0f)) * deltaTime * this->strafeInput * MOVEMENT_SPEED;
	this->position->x += sin(glm::radians(*this->rotation - 90.0f)) * deltaTime * this->strafeInput * MOVEMENT_SPEED;
}

void Cucumber::mouseMoved(float deltaX, float deltaY)
{
	this->camera->mouseMoved(deltaX, deltaY);
	*this->rotation = -camera->getYaw() -90.0f;
}

void Cucumber::pollKeyboard(GLFWwindow* window)
{
	this->moveInput = 0.0f;
	this->strafeInput = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->moveInput += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->strafeInput -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->moveInput -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->strafeInput += 1.0f;
	}
}
