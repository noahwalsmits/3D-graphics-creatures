#include "Material.h"

Material::~Material()
{
	delete this->texture;
}
