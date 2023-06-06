#include "MeshGroup.h"

MeshGroup::MeshGroup(const std::vector<Mesh*>& meshes)
{
	this->meshes = meshes;
}

MeshGroup::~MeshGroup()
{
	for (const Mesh* mesh : this->meshes)
	{
		delete mesh;
	}
}

void MeshGroup::draw() const
{
	for (const Mesh* mesh : this->meshes)
	{
		mesh->draw();
	}
}
