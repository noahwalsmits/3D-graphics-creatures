#include "Mesh.h"

Mesh::Mesh(const std::vector<tigl::Vertex>& vertices, Material* material, GLenum shape)
{
	this->vbo = tigl::createVbo(vertices);
	this->material = material;
	this->shape = shape;
}

Mesh::~Mesh()
{
	delete this->vbo;
	delete this->material;
}

void Mesh::draw(tigl::internal::Shader& shader) const
{
	this->material->texture->bind();
	//shader.setLightAmbient(0, this->material->ambientColor);
	//shader.setLightDiffuse(0, this->material->diffuseColor);
	//shader.setLightSpecular(0, this->material->specularColor);
	shader.setShinyness(this->material->shinyness);
	tigl::drawVertices(this->shape, this->vbo);
}
