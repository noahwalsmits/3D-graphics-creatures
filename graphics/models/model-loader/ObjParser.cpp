#include "ObjParser.h"
#include <fstream>
#include <glm/glm.hpp>

#include <iostream>

ObjParser::ObjParser() : ModelParser()
{
}

std::vector<Mesh> ObjParser::parseModel(const std::string& assetPath) const
{
	std::string filePath = "assets/" + assetPath;
	std::vector<Mesh> meshes;

	std::ifstream objFile(filePath.c_str());
	if (!objFile.is_open())
	{
		throw std::runtime_error("model file " + filePath + " could not be opened");
	}

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	while (!objFile.eof())
	{
		std::string line;
		std::getline(objFile, line);

		std::string command = line.substr(0, line.find(" "));
		std::cout << command << std::endl;
	}


	return meshes;
}
