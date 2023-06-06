#pragma once
#include <vector>
#include "tigl.h"
#include <graphics/models/Material.h>

class Mesh
{
public:
	/// <summary>
	/// Creates a Mesh from a number of vertices and a material. The vertices are used to create a 
	/// VBO and can safely be discarded afterwards.
	/// </summary>
	Mesh(const std::vector<tigl::Vertex>& vertices, Material* material, GLenum shape = GL_TRIANGLES);
	Mesh(const Mesh& other);
	Mesh& operator=(const Mesh& other);
	~Mesh();

	void draw() const;
	void deleteResources();

private:
	tigl::VBO* vbo;
	Material* material;
	GLenum shape;
};
