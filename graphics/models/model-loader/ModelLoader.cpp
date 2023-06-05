#include "ModelLoader.h"
#include <stdexcept>
#include <graphics/models/model-loader/ObjParser.h>

ModelLoader::ModelLoader()
{
	this->fileParsers.emplace(".obj", new ObjParser()); //TODO delete the map entries
}

MeshGroup ModelLoader::loadModel(const std::string& filePath)
{
	//TODO check if we already have it

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
	
	return MeshGroup(this->fileParsers[fileExtention]->parseModel(filePath));
}
