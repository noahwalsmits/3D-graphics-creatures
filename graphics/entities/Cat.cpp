#include "Cat.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lib/glm/glm/gtc/quaternion.hpp>

Cat::Cat(const glm::vec3& position, const Cucumber& player) : player(player), Entity()
{
	this->position = std::make_shared<glm::vec3>(position);
	this->currentRotation = std::make_shared<float>(0.0f);

	//find angle to face towards the player
	glm::mat4 rotation = glm::lookAt(*this->position, this->player.getPosition(), glm::vec3(0, 1, 0));
	glm::vec3 angles = glm::degrees(glm::eulerAngles(glm::inverse(glm::quat_cast(rotation))));
	this->desiredRotation = angles.y;
	if (std::fabs(angles.z) >= 90.0f)
	{
		this->desiredRotation = 180.0f - angles.y;
	}
	this->desiredRotation += 180.0f;
	*this->currentRotation = this->desiredRotation;

	//pick random model variation
	switch (rand() % 2)
	{
	case 0:
		this->models.push_back(Model("cat_orange/12221_Cat_v1_l3.obj", position));
		break;
	case 1:
		this->models.push_back(Model("cat_black/12222_Cat_v1_l3.obj", position));
		break;
	}

	for (Model& model : this->models)
	{
		model.position = this->position;
		model.rotationYaw = this->currentRotation;
		*model.scale = 0.05f;
		*model.rotationPitch = -90.0f;
	}
}

void Cat::update(float deltaTime)
{
	this->movementSpeed = 0.0f;

	//run away from the player
	float distance = glm::distance(*this->position, this->player.getPosition());
	if (distance <= DETECTION_RANGE)
	{
		//find angle to face away from the player
		glm::mat4 rotation = glm::lookAt(*this->position, this->player.getPosition(), glm::vec3(0, 1, 0));
		glm::vec3 angles = glm::degrees(glm::eulerAngles(glm::inverse(glm::quat_cast(rotation))));
		this->desiredRotation = angles.y;
		if (std::fabs(angles.z) >= 90.0f)
		{
			this->desiredRotation = 180.0f - angles.y;
		}

		//approaches 1 as distance decreases towards MAX_SPEED_DISTANCE
		float speedMultiplier = std::min((DETECTION_RANGE - distance + MAX_SPEED_DISTANCE) / DETECTION_RANGE, 1.0f);
		this->movementSpeed = MAX_FLEEING_SPEED * speedMultiplier;
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
