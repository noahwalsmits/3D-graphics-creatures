#pragma once
#include<string>

class Texture
{
public:
	Texture(const std::string& filePath);
	void bind();

private:
	unsigned int id;
};

