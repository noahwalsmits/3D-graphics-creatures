#pragma once
#include <vector>
#include <graphics/models/Model.h>

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void update(float deltaTime) = 0;
	void draw(tigl::internal::Shader& shader) const;

protected:
	std::vector<Model> models;
};

