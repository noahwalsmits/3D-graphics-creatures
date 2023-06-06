#pragma once
#include <vector>
#include <graphics/models/Mesh.h>

class MeshGroup
{
public:
	MeshGroup(const std::vector<Mesh*>& meshes);
	MeshGroup(const MeshGroup& other) = delete;
	MeshGroup& operator=(const MeshGroup& other) = delete;
	~MeshGroup();

	void draw() const;
	//TODO create destructor that also frees all resources from OpenGL

private:
	std::vector<Mesh*> meshes;
};

