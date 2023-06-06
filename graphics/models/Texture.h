#pragma once
#include<string>

class Texture
{
public:
	/// <summary>
	/// Creates a texture from an image file and allocates the GPU resources for it.
	/// </summary>
	/// <param name="filePath">path to the image file</param>
	Texture(const std::string& filePath);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	~Texture();

	void bind();

private:
	unsigned int id;
};
