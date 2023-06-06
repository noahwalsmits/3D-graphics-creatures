#pragma once
#include <graphics/models/Texture.h>

/// <summary>
/// Holds the material information required to properly draw the surface of a Mesh.
/// </summary>
class Material
{
public:
	std::string name;
	Texture* texture;

	Material() = default;
	Material(const Material& other) = delete;
	Material& operator=(const Material& other) = delete;
	~Material();
};
