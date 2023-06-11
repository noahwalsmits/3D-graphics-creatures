#pragma once
#include <glm/glm.hpp>
#include <graphics/models/Texture.h>

/// <summary>
/// Holds the material information required to properly draw the surface of a Mesh.
/// </summary>
class Material
{
public:
	std::string name;
	Texture* texture;
	float shinyness = 0.0f;
	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

	Material() = default;
	Material(const Material& other) = delete;
	Material& operator=(const Material& other) = delete;
	~Material();
};
