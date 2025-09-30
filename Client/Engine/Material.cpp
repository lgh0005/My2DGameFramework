#include "pch.h"
#include "Material.h"
#include "ITexture.h"
#include "Shader.h"

Material::Material(const string& name, const shared_ptr<ITexture>& texture, const shared_ptr<Shader>& shader)
	: Super(name), _texture(texture), _shader(shader)
{

}

void Material::Bind()
{
	_shader->Bind();
	_texture->Bind();
}

