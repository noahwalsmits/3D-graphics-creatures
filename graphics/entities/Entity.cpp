#include "Entity.h"

void Entity::draw(tigl::internal::Shader& shader)
{
	for (const Model& model : this->models)
	{
		model.draw(shader);
	}
}
