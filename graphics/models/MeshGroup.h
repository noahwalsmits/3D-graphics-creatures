#pragma once
#include <vector>
#include <graphics/models/Mesh.h>

/// <summary>
/// The graphical data to draw a model.
/// Deleting a MeshGroup will also delete its underlying Meshes and free the allocated GPU resources.
/// </summary>
class MeshGroup
{
public:
	MeshGroup(const std::vector<Mesh*>& meshes);
	MeshGroup(const MeshGroup& other) = delete;
	MeshGroup& operator=(const MeshGroup& other) = delete;
	~MeshGroup();

	void draw(tigl::internal::Shader& shader) const;

private:
	std::vector<Mesh*> meshes;
};

