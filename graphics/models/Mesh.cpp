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

void Mesh::draw() const
{
	this->material->texture->bind();
	tigl::drawVertices(this->shape, this->vbo);
}
