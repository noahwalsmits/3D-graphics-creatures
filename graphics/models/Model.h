#pragma once
#include <string>
#include "tigl.h"
#include <graphics/models/MeshGroup.h>

class Model
{
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); //location do draw the model
	float rotationYaw = 0.0f; //z-axis rotation in degrees
	float rotationPitch = 0.0f; //y-axis rotation in degrees
	float rotationRoll = 0.0f; //x-axis rotation in degrees
	glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f); //offset to position applied after rotation
	float scale = 1.0f; //size to draw the model with

	Model(const std::string& filePath, const glm::vec3& position);

	void draw(tigl::internal::Shader& shader) const;

private:
	std::shared_ptr<MeshGroup> meshGroup;
};

