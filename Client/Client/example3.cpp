#include "pch.h"
#include "example3.h"

#include "Engine/GameObject.h"
#include "Engine/UICheckBox.h"
#include "Engine/Shader.h"
#include "Engine/ITexture.h"
#include "Engine/Texture.h"

example3::example3(const string& name) : Super(name)
{

}

example3::~example3()
{
}

void example3::Init()
{
	Super::Init();
	auto self = GetSelf<example3>();
	_checkBox = static_pointer_cast<UICheckBox>(_owner.lock()->GetRenderable("CheckBox"));
	
	_checkBox->OnToggleEvent
	(
		[self]() { self->MouseToggle(); },
		UI::UIEventPolicy::Immediate,
		EMPTY_VEC2, EMPTY_VEC2
	);
}

void example3::Update()
{
	Super::Update();
}

void example3::MouseToggle()
{
	AUDIO.PlaySFX("WHOOSH");

	if (_checkBox->IsToggled())
	{
		_checkBox->SetTexture(RESOURCE.GetResource<Texture>("CLICKED"));
	}
	else
	{
		_checkBox->SetTexture(RESOURCE.GetResource<Texture>("CheckBoxTexture"));
	}
}