#pragma once
#include <vector>
#include <graphics/models/Mesh.h>

class MeshGroup
{
public:
	MeshGroup(const std::vector<Mesh>& meshes);

	void draw() const;

	//TODO implement Model
	//TODO create destructor that also frees all resources from OpenGL

private:
	std::vector<Mesh> meshes;
};

