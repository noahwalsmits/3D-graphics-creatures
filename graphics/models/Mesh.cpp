#include "Mesh.h"

Mesh::Mesh(const std::vector<tigl::Vertex>& vertices, Material* material, GLenum shape)
{
	this->vbo = tigl::createVbo(vertices);
	this->material = material;
	this->shape = shape;
}

Mesh::Mesh(const Mesh& other)
{
	this->vbo = new tigl::VBO(*other.vbo);
	this->material = new Material(*other.material);
	this->shape = other.shape;
}

Mesh& Mesh::operator=(const Mesh& other)
{
	if (this != &other)
	{
		delete this->vbo;
		this->vbo = new tigl::VBO(*other.vbo);
		delete this->material;
		this->material = new Material(*other.material);
		this->shape = other.shape;
	}
	return *this;
}

Mesh::~Mesh()
{
	//TODO
}

void Mesh::draw() const
{
	this->material->texture->bind();
	tigl::drawVertices(this->shape, this->vbo);
}
