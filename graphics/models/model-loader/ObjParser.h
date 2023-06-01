#pragma once
#include <string>
#include <vector>
#include <graphics/models/model-loader/ModelParser.h>

class ObjParser : public ModelParser
{
public:
	ObjParser();
	~ObjParser() = default;

	std::vector<Mesh> parseModel(const std::string& assetPath) const override;

private:
	std::vector<std::string> splitArguments(std::string line) const;
};

