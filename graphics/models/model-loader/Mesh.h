#pragma once
#include <vector>
#include "tigl.h"

class Mesh
{
public:
	Mesh(std::vector<tigl::Vertex> vertices);

	tigl::VBO* createVBO();

private:
	std::vector<tigl::Vertex> vertices;
};

