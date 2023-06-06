#pragma once
#include <vector>
#include <graphics/models/Mesh.h>

class MeshGroup
{
public:
	MeshGroup(const std::vector<Mesh>& meshes);
	MeshGroup(const Mesh& other) = delete;
	MeshGroup& operator=(const Mesh& other) = delete;
	~MeshGroup();

	void draw() const;
	//TODO create destructor that also frees all resources from OpenGL
	//Mesh, Material and Texture can all be copied and deleted for ease of parsing different types of files.
	//There is only one MeshGroup however, and deleting it will clear all it's resources from the GPU

private:
	std::vector<Mesh> meshes;
};

