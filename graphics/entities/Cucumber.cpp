#include "Cucumber.h"

Cucumber::Cucumber(const glm::vec3& position) : Entity(), Controllable()
{
	this->position = std::make_shared<glm::vec3>(position);
	this->models.push_back(Model("Egg 1/kart_YS_b.obj", position));
	this->camera = new OrbitalCamera(position);

	for (Model& model : this->models)
	{
		model.position = this->position;
	}
}

Cucumber::~Cucumber()
{
	delete this->camera;
}

void Cucumber::update(float deltaTime)
{
	//update position
	this->position->z += cos(glm::radians(this->rotation)) * deltaTime * this->moveSpeed * 5.0f;
	this->position->x += sin(glm::radians(this->rotation)) * deltaTime * this->moveSpeed * 5.0f;
	
	this->position->x -= cos(glm::radians(this->rotation)) * deltaTime * this->strafeSpeed * 5.0f;
	this->position->z -= sin(glm::radians(this->rotation)) * deltaTime * this->strafeSpeed * 5.0f;
	
	//TODO camera tracking
}

void Cucumber::mouseMoved(float deltaX, float deltaY)
{
	this->camera->mouseMoved(deltaX, deltaY);
	this->rotation = camera->getYaw();
}

void Cucumber::pollKeyboard(GLFWwindow* window)
{
	this->moveSpeed = 0.0f;
	this->strafeSpeed = 0.0f;

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
