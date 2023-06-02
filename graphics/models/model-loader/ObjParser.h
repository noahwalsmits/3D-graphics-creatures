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

	std::vector<Mesh> parseModel(const std::string& assetPath) const override;

private:
	std::vector<std::string> splitArguments(std::string line, const std::string& delimiter) const;
	Material readMaterial(const std::string& filePath) const;
};

