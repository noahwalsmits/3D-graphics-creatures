#pragma once
#include <graphics/models/Model.h>
#include <string>

class ModelLoader
{
public:
	Model loadModel(const std::string& filePath);
};

