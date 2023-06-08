#include "Cat.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lib/glm/glm/gtc/quaternion.hpp>

#include <iostream>

Cat::Cat(const glm::vec3& position, const Cucumber& player) : player(player), Entity()
{
	this->position = std::make_shared<glm::vec3>(position);
	this->currentRotation = std::make_shared<float>(0.0f);
	this->models.push_back(Model("Egg 1/kart_YS_b.obj", position));

	for (Model& model : this->models)
	{
		model.position = this->position;
		model.rotationYaw = this->currentRotation;
	}
}

void Cat::update(float deltaTime)
{
	if (glm::distance(*this->position, this->player.getPosition()) < DETECTION_RANGE)
	{
		glm::mat4 rotation = glm::lookAt(*this->position, this->player.getPosition(), glm::vec3(0, 1, 0));
		glm::vec3 angles = glm::degrees(glm::eulerAngles(glm::inverse(glm::quat_cast(rotation))));
		*this->currentRotation = angles.y;
		if (std::fabs(angles.z) >= 90.0f)
		{
			*this->currentRotation = 180.0f - angles.y;
		}
		//std::cout << angles.x << ", " << angles.y << ", " << angles.z << ", current: " << *this->currentRotation << std::endl;
	}
}
