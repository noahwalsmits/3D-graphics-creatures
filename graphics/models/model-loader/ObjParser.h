#pragma once
#include <string>
#include <vector>
#include <graphics/models/model-loader/ModelParser.h>
#include <graphics/models/Material.h>

class ObjParser : public ModelParser
{
public:
	ObjParser();
	~ObjParser() = default;

	std::vector<Mesh*> parseModel(const std::string& assetPath) const override;

private:
	std::vector<std::string> splitArguments(std::string line, const std::string& delimiter) const;

	/// <summary>
	/// Creates a Vertex from a face argument.
	/// </summary>
	/// <param name="vertexIndices">a face argument such as "1/2/3", "1/2", "1//3" or "1"</param>
	/// <param name="positions">the positions read from the .obj file</param>
	/// <param name="textureCoords">the texture coordinates read from the .obj file</param>
	/// <param name="normals">the normals read from the obj file</param>
	/// <returns>a vertex</returns>
	tigl::Vertex parseVertex(const std::string& vertexIndices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals) const;
	
	/// <summary>
	/// Reads the materials from an mtl file and adds them to the provided vector.
	/// </summary>
	/// <param name="filePath">path to the .mtl file</param>
	/// <param name="loadedMaterials">list of the already loaded materials to add the newly read ones to</param>
	void readMaterials(const std::string& filePath, std::vector<Material*>& loadedMaterials) const;
};

