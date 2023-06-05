#include "Model.h"
#include <graphics/models/model-loader/ModelLoader.h>

Model::Model(const std::string& filePath, const glm::vec3& position)
{
	this->meshGroup = MODEL_LOADER.loadModel(filePath);
	this->position = position;
}

void Model::draw(tigl::internal::Shader& shader) const
{
	this->meshGroup->draw();
}
