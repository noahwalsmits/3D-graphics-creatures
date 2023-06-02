#include "Mesh.h"

Mesh::Mesh(std::vector<tigl::Vertex> vertices)
{
	this->vertices = vertices;
}

tigl::VBO* Mesh::createVBO()
{
	return tigl::createVbo(this->vertices);
}
