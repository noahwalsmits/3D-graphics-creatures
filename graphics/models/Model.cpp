#include "Model.h"
#include <graphics/models/model-loader/ModelLoader.h>
#include <lib/glm/glm/ext/matrix_transform.hpp>

Model::Model(const std::string& filePath, const glm::vec3& position)
{
	this->meshGroup = MODEL_LOADER.loadModel(filePath);
	this->position = std::make_shared<glm::vec3>(position);
	this->rotationYaw = std::make_shared <float>(0.0f);
	this->rotationPitch = std::make_shared <float>(0.0f);
	this->rotationRoll = std::make_shared <float>(0.0f);
	this->offset = std::make_shared<glm::vec3>(0.0f, 0.0f, 0.0f);
	this->scale = std::make_shared <float>(1.0f);
}

void Model::draw(tigl::internal::Shader& shader) const
{
	//move model
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), *this->position);
	//rotate model
	modelMatrix = glm::rotate(modelMatrix, glm::radians(*this->rotationYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(*this->rotationPitch), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(*this->rotationRoll), glm::vec3(0.0f, 0.0f, 1.0f));
	//offset model
	modelMatrix = glm::translate(modelMatrix, *this->offset);
	//scale model
	modelMatrix = glm::scale(modelMatrix, glm::vec3(*this->scale, *this->scale, *this->scale));
	//update the model uniform
	shader.setModelMatrix(modelMatrix);

	this->meshGroup->draw(shader);
}
