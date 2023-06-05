#include "ModelLoader.h"
#include <stdexcept>
#include <graphics/models/model-loader/ObjParser.h>

ModelLoader MODEL_LOADER;

ModelLoader::ModelLoader()
{
	this->fileParsers.emplace(".obj", new ObjParser());
}

ModelLoader::~ModelLoader()
{
	//clean up model parsers
	for (auto parser : this->fileParsers)
	{
		delete parser.second;
	}
}

MeshGroup ModelLoader::loadModel(const std::string& filePath)
{
	//check if we already have it loaded
	if (this->loadedModels.count(filePath) == 1)
	{
		return *this->loadedModels[filePath]; //TODO return shared pointer instead
	}

	//check filetype for parser
	int fileExtentionIndex = filePath.find_last_of(".");
	if (fileExtentionIndex == std::string::npos)
	{
		throw std::runtime_error("model file " + filePath + " format not recognized");
	}
	std::string fileExtention = filePath.substr(fileExtentionIndex);
	if (this->fileParsers.count(fileExtention) != 1)
	{
		throw std::runtime_error("model format " + fileExtention + " is not supported");
	}

	//parse model and keep it saved
	MeshGroup meshGroup = MeshGroup(this->fileParsers[fileExtention]->parseModel(filePath));
	this->loadedModels.emplace(filePath, std::make_shared<MeshGroup>(meshGroup));
	return meshGroup;
}
