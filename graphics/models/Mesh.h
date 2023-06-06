#pragma once
#include <vector>
#include "tigl.h"
#include <graphics/models/Material.h>

/// <summary>
/// Represents a group of vertices with a material which can be drawn.
/// The GPU resources to draw a Mesh are allocated when creating an instance.
/// These resources are freed when the Mesh is destroyed.
/// </summary>
class Mesh
{
public:
	/// <summary>
	/// Creates a Mesh from a number of vertices and a material. The vertices are used to create a 
	/// VBO and can safely be discarded afterwards.
	/// </summary>
	Mesh(const std::vector<tigl::Vertex>& vertices, Material* material, GLenum shape = GL_TRIANGLES);
	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh& other) = delete;
	~Mesh();

	void draw() const;

private:
	tigl::VBO* vbo;
	Material* material;
	GLenum shape;
};
