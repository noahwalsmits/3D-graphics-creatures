#pragma once
#include <graphics/models/model-loader/ModelParser.h>

class ObjParser : public ModelParser
{
public:
	ObjParser();
	~ObjParser() = default;

	virtual std::vector<Mesh> parseModel(const std::string& filePath) const override;
};

