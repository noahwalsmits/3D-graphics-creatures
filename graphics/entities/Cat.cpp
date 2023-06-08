#include "Cat.h"

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
}
