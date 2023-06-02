#include "Mesh.h"

Mesh::Mesh(std::vector<tigl::Vertex> vertices, Material* material)
{
	this->vertices = vertices;
	this->material = material;
}

tigl::VBO* Mesh::createVBO()
{
	return tigl::createVbo(this->vertices);
}
