#pragma once
#include <vector>
#include "tigl.h"
#include <graphics/models/Material.h>

class Mesh
{
public:
	Mesh(std::vector<tigl::Vertex> vertices, Material* material);
	//TODO store VBO instead of vertices
	//TODO add draw function
	//TODO create destructor

	tigl::VBO* createVBO();

private:
	std::vector<tigl::Vertex> vertices;
	Material* material;
};

