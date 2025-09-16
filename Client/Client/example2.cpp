#include "pch.h"
#include "example2.h"

#include "Engine/GameObject.h"
#include "Engine/UIButton.h"
#include "Engine/Shader.h"
#include "Engine/ITexture.h"
#include "Engine/Texture.h"

example2::example2(const string& name) : Super(name)
{
}

example2::~example2()
{
}

void example2::Init()
{
	Super::Init();
	auto self = GetSelf<example2>();
	_button = static_pointer_cast<UIButton>(_owner.lock()->GetRenderable("Button"));
	_button->OnHoveredEvent([self]() { self->MouseHovered(); });
	_button->OnClickedEvent([self]() { self->MouseClicked(); });
	_button->OnExitEvent([self]() { self->MouseExit(); });
}

void example2::Update()
{
	Super::Update();
}

void example2::MouseHovered()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("HOVERED"));
}

void example2::MouseExit()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("buttonTexture"));
}

void example2::MouseClicked()
{
	cout << "Clicked!" << endl;
}
