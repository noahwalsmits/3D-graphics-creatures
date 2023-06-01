#pragma once
#include <string>
#include <vector>
#include <graphics/models/model-loader/Mesh.h>

class ModelParser
{
public:
	virtual ~ModelParser() = default;

	virtual std::vector<Mesh> parseModel(const std::string& filePath) const = 0;
};

