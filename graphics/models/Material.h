#pragma once
#include <graphics/models/Texture.h>

class Material
{
public:
	std::string name;
	Texture* texture;

	Material() = default;
	Material(const Material& other);
	Material& operator=(const Material& other);
	~Material();
};
