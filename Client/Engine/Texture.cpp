#include "pch.h"
#include "Texture.h"
#include "Camera.h"

Texture::Texture(const string& name, const string& filePath) : Super(name, filePath)
{
}

Texture::~Texture()
{
}

void Texture::Awake()
{
	Super::Awake();
}

void Texture::Render(shared_ptr<Shader> shader, glm::mat4 model, shared_ptr<Camera> camera)
{
	Super::Render(shader, model, camera);
}
