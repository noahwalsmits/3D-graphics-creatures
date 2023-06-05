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
	~ModelLoader();

	MeshGroup loadModel(const std::string& filePath);

	//TODO check all shared pointers for usage count and remove if we're the last ones

private:
	std::map<std::string, ModelParser*> fileParsers; //<file extention, appropriate parser>
	std::map<std::string, std::shared_ptr<MeshGroup>> loadedModels; //<file path, appropriate meshgroup>
};

