#pragma once
#include <graphics/models/Model.h>
#include <string>
#include <map>
#include <graphics/models/MeshGroup.h>
#include <graphics/models/model-loader/ModelParser.h>

class ModelLoader
{
public:
	ModelLoader();

	MeshGroup loadModel(const std::string& filePath);

	//TODO check all shared pointers for usage count and remove if we're the last ones

private:
	std::map<std::string, ModelParser*> fileParsers;
};

