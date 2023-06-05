#pragma once
#include <string>
#include "tigl.h"
#include <graphics/models/MeshGroup.h>

class Model
{
public:
	glm::vec3 position;
	float rotationYaw;
	float rotationPitch;
	float rotationRoll;
	glm::vec3 offset;
	float scale;

	Model(const std::string& filePath, const glm::vec3& position);

	void draw(tigl::internal::Shader& shader) const;

private:
	std::shared_ptr<MeshGroup> meshGroup;
};

