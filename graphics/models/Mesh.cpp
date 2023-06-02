#include "Mesh.h"

Mesh::Mesh(const std::vector<tigl::Vertex>& vertices, Material* material)
{
	this->vbo = tigl::createVbo(vertices);
	this->material = material;
}

void Mesh::draw() const
{
	this->material->texture->bind();
	tigl::drawVertices(GL_TRIANGLES, this->vbo);
}
