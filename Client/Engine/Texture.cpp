#include "pch.h"
#include "Texture.h"

Texture::Texture(const string& name, const string& filePath) : Super(name, filePath)
{
}

Texture::~Texture()
{
}

void Texture::Init()
{
	Super::Init();
}

void Texture::Render(shared_ptr<Shader> shader, glm::mat4 model)
{
	Super::Render(shader, model);
}
