#include "pch.h"
#include "Font.h"

Font::Font(const string& name, const string& filePath) : Super(name, filePath)
{
}

Font::~Font()
{
}

void Font::Init()
{
}

void Font::Render(shared_ptr<Shader> shader, glm::mat4 model)
{
	Super::Render(shader, model);
}
