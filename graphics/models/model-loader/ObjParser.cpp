#include "ObjParser.h"
#include <fstream>
#include <glm/glm.hpp>
#include "tigl.h"

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

	std::vector<tigl::Vertex> indexed_vertices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	while (!objFile.eof())
	{
		std::string line;
		std::getline(objFile, line);
		std::vector<std::string> arguments = splitArguments(line, " ");
		
		if (arguments[0] == "v") //read vertex
		{
			temp_vertices.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
		else if (arguments[0] == "vt") //read uv
		{
			temp_uvs.push_back(glm::vec2(std::stof(arguments[1]), std::stof(arguments[2])));
		}
		else if (arguments[0] == "vn") //read normal
		{
			temp_normals.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
		else if (arguments[0] == "f") //read face
		{
			for (int i = 1; i < arguments.size(); i++)
			{
				std::vector<std::string> faceIndices = splitArguments(arguments[i], "/"); //split face to get vertex/uv/normal
				assert(faceIndices.size() == 3); //TODO support other format
				int vertexIndex = std::stoi(faceIndices[0]) - 1;
				int uvIndex = std::stoi(faceIndices[1]) - 1;
				int normalIndex = std::stoi(faceIndices[2]) - 1;
				indexed_vertices.push_back(tigl::Vertex::PTN(temp_vertices[vertexIndex], temp_uvs[uvIndex], temp_normals[normalIndex]));
			}
		}
		else if (arguments[0] == "mtllib") //load material
		{
			//TODO
		}
		else if (arguments[0] == "usemtl") //
		{
			//TODO all faces after this command will use the specified material
			//so here we add all previously read faces into a mesh with the previously read material
		}
	}
	//TODO after we are done reading we need to add the remaining faces into a mesh with the last material

	meshes.push_back(Mesh(indexed_vertices));
	return meshes;
}

std::vector<std::string> ObjParser::splitArguments(std::string line, const std::string& delimiter) const
{
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

Material ObjParser::readMaterial(const std::string& filePath)
{
	return Material();
}
