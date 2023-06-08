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
	this->movementSpeed = 0.0f;

	//run away from the player
	if (glm::distance(*this->position, this->player.getPosition()) < DETECTION_RANGE)
	{
		glm::mat4 rotation = glm::lookAt(*this->position, this->player.getPosition(), glm::vec3(0, 1, 0));
		glm::vec3 angles = glm::degrees(glm::eulerAngles(glm::inverse(glm::quat_cast(rotation))));
		this->desiredRotation = angles.y;
		if (std::fabs(angles.z) >= 90.0f)
		{
			this->desiredRotation = 180.0f - angles.y;
		}
		this->movementSpeed = FLEEING_SPEED; //TODO base this on distance
	}

	//gradually turn model towards desired rotation
	float rotationDifference = this->desiredRotation - *this->currentRotation;
	if (rotationDifference > 180.0f)
	{
		rotationDifference -= 360.0f;
	}
	else if (rotationDifference < -180.0f)
	{
		rotationDifference += 360.0f;
	}
	*this->currentRotation += rotationDifference * deltaTime * ROTATION_SPEED;

	//move in desired direction
	this->position->z += cos(glm::radians(this->desiredRotation)) * deltaTime * this->movementSpeed;
	this->position->x += sin(glm::radians(this->desiredRotation)) * deltaTime * this->movementSpeed;
}
