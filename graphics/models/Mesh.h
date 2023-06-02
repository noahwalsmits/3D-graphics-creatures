#pragma once
#include <vector>
#include "tigl.h"
#include <graphics/models/Material.h>

class Mesh
{
public:
	Mesh(const std::vector<tigl::Vertex>& vertices, Material* material);
	//TODO store shape type here
	//TODO support missing values for obj faces
	//TODO create destructor that also frees all resources from OpenGL
	//TODO fix the copy constructors so the model can get a working list of these

	void draw() const;

private:
	tigl::VBO* vbo;
	Material* material;
};
