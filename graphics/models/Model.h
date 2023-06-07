#pragma once
#include <string>
#include "tigl.h"
#include <graphics/models/MeshGroup.h>

class Model
{
public:
	//models start out with internal values
	//these can be replaced with different pointers so that multiple models can read from the same values
	std::shared_ptr<glm::vec3> position; //location to draw the model
	std::shared_ptr<float> rotationYaw; //z-axis rotation in degrees
	std::shared_ptr<float> rotationPitch; //y-axis rotation in degrees
	std::shared_ptr<float> rotationRoll; //x-axis rotation in degrees
	std::shared_ptr<glm::vec3> offset; //offset to position applied after rotation
	std::shared_ptr<float> scale; //size to draw the model with

	Model(const std::string& filePath, const glm::vec3& position);

	void draw(tigl::internal::Shader& shader) const;

private:
	std::shared_ptr<MeshGroup> meshGroup;
};

