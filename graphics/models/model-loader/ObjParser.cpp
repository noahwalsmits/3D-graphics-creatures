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
	std::cout << "loading model " << filePath << std::endl;
	std::vector<Mesh> meshes;

	std::ifstream objFile(filePath.c_str());
	if (!objFile.is_open())
	{
		throw std::runtime_error("model file " + filePath + " could not be opened");
	}

	std::vector<glm::vec3> readPositions;
	std::vector<glm::vec2> readTexCoords;
	std::vector<glm::vec3> readNormals;
	std::vector<tigl::Vertex> readVertices;
	std::vector<Material*> loadedMaterials;
	Material* currentMaterial = nullptr;

	while (!objFile.eof())
	{
		std::string line;
		std::getline(objFile, line);
		std::vector<std::string> arguments = splitArguments(line, " ");
		
		if (arguments[0] == "v") //read position
		{
			readPositions.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
		else if (arguments[0] == "vt") //read texture coordinates
		{
			readTexCoords.push_back(glm::vec2(std::stof(arguments[1]), std::stof(arguments[2])));
		}
		else if (arguments[0] == "vn") //read normal
		{
			readNormals.push_back(glm::vec3(std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3])));
		}
		else if (arguments[0] == "f") //read face
		{
			for (int i = 1; i < arguments.size(); i++) //read each vertex
			{
				readVertices.push_back(parseVertex(arguments[i], readPositions, readTexCoords, readNormals));
			}
		}
		else if (arguments[0] == "mtllib") //load material
		{
			std::string directoryPath = filePath.substr(0, filePath.find_last_of("/"));
			readMaterials(directoryPath + "/" + arguments[1], loadedMaterials);
		}
		else if (arguments[0] == "usemtl") //use material
		{
			//add all previously read faces into a mesh with the previously read material
			if (readVertices.size() > 0 && currentMaterial)
			{
				meshes.push_back(Mesh(readVertices, currentMaterial));
				readVertices.clear();
			}
			//set new current material
			for (Material* material : loadedMaterials)
			{
				if (material->name == arguments[1])
				{
					currentMaterial = material;
				}
			}
		}
	}
	//after we are done reading we need to add the remaining faces into a mesh with the last material
	if (readVertices.size() > 0 && currentMaterial)
	{
		meshes.push_back(Mesh(readVertices, currentMaterial));
		readVertices.clear();
	}

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

tigl::Vertex ObjParser::parseVertex(const std::string& vertexIndices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals) const
{
	std::vector<std::string> arguments = splitArguments(vertexIndices, "/"); //split face to get vertex/uv/normal
	int vertexIndex;
	int uvIndex;
	int normalIndex;

	if (arguments.size() == 3)
	{
		if (arguments[2].empty()) //positions and normals
		{
			vertexIndex = std::stoi(arguments[0]) - 1;
			normalIndex = std::stoi(arguments[2]) - 1;
			return tigl::Vertex::PN(positions[vertexIndex], normals[normalIndex]);
		}
		else //positions, textures and normals
		{
			vertexIndex = std::stoi(arguments[0]) - 1;
			uvIndex = std::stoi(arguments[1]) - 1;
			normalIndex = std::stoi(arguments[2]) - 1;
			return tigl::Vertex::PTN(positions[vertexIndex], textureCoords[uvIndex], normals[normalIndex]);
		}
	}
	if (arguments.size() == 2) //positions and textures
	{
		vertexIndex = std::stoi(arguments[0]) - 1;
		uvIndex = std::stoi(arguments[1]) - 1;
		return tigl::Vertex::PT(positions[vertexIndex], textureCoords[uvIndex]);
	}
	if (arguments.size() == 1) //positions
	{
		vertexIndex = std::stoi(arguments[0]) - 1;
		return tigl::Vertex::P(positions[vertexIndex]);
	}
	throw std::runtime_error("could not parse vertex argument " + vertexIndices);
}

void ObjParser::readMaterials(const std::string& filePath, std::vector<Material*>& loadedMaterials) const
{
	std::cout << "\tloading material " << filePath << std::endl;
	std::ifstream mtlFile(filePath.c_str());
	if (!mtlFile.is_open())
	{
		throw std::runtime_error("material file " + filePath + " could not be opened");
	}

	Material* currentMaterial = nullptr;

	while (!mtlFile.eof())
	{
		std::string line;
		std::getline(mtlFile, line);
		std::vector<std::string> arguments = splitArguments(line, " ");

		if (arguments[0] == "newmtl") //create new material
		{
			if (currentMaterial)
			{
				loadedMaterials.push_back(currentMaterial);
			}
			currentMaterial = new Material();
			currentMaterial->name = arguments[1];
		}
		else if (arguments[0] == "map_Kd") //load diffuse texture
		{
			std::string directoryPath = filePath.substr(0, filePath.find_last_of("/"));
			currentMaterial->texture = new Texture(directoryPath + "/" + arguments[1]);
		}
		//TODO other parameter types
	}
	//add the last material after we are done reading
	if (currentMaterial)
	{
		loadedMaterials.push_back(currentMaterial);
	}
}
