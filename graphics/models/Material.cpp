#include "Material.h"

Material::Material(const Material& other)
{
	this->name = other.name;
	this->texture = new Texture(*other.texture);
}

Material& Material::operator=(const Material& other)
{
	if (this != &other)
	{
		delete this->texture;
		this->texture = new Texture(*other.texture);
	}
	return *this;
}

Material::~Material()
{
	delete this->texture;
}
