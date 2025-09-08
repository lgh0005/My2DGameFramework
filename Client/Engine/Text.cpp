#include "pch.h"
#include "Text.h"

Text::Text(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader)
	: Super(name, texture, shader)
{
}

Text::~Text()
{

}

void Text::Awake(shared_ptr<GameObject> owner)
{
	Super::Awake(owner);
}

void Text::Render(const shared_ptr<Camera>& camera)
{
	Super::Render(camera);
}
