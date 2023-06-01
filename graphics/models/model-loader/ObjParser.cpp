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
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	while (!objFile.eof())
	{
		std::string line;
		std::getline(objFile, line);
		std::vector<std::string> arguments = splitArguments(line);
		
		if (arguments[0] == "v")
		{
			temp_vertices.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
		else if (arguments[0] == "vt")
		{
			temp_uvs.push_back(glm::vec2(std::stof(arguments[1]), std::stof(arguments[2])));
		}
		else if (arguments[0] == "vn")
		{
			temp_normals.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
	}

	return meshes;
}

std::vector<std::string> ObjParser::splitArguments(std::string line) const
{
	std::string delimiter = " ";
	std::vector<std::string> arguments;
	int index = 0;
	while (line.find(delimiter) != std::string::npos)
	{
		index = line.find(delimiter);
		arguments.push_back(line.substr(0, index));
		line = line.substr(index + delimiter.length());
	}
	arguments.push_back(line);

	return arguments;
}
