#include "pch.h"
#include "example2.h"

#include "Engine/GameObject.h"
#include "Engine/UIButton.h"
#include "Engine/Shader.h"
#include "Engine/ITexture.h"
#include "Engine/Texture.h"
#include "example3.h"

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
	_button->OnHoveredEvent
	(
		[self]() { self->MouseHovered(); }, 
		UI::UIEventPolicy::Immediate, 
		EMPTY_VEC2, EMPTY_VEC2
	);

	_button->OnClickedEvent
	(
		[self]() { self->MouseClickedDeferred(); },
		UI::UIEventPolicy::Deferred,
		EMPTY_VEC2, EMPTY_VEC2
	);

	_button->OnClickedEvent
	(
		[self]() { self->MouseClickedImmediate(); },
		UI::UIEventPolicy::Immediate,
		EMPTY_VEC2, EMPTY_VEC2
	);

	_button->OnExitEvent
	(
		[self]() { self->MouseExit(); },
		UI::UIEventPolicy::Deferred,
		EMPTY_VEC2, EMPTY_VEC2
	);
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

void example2::MouseClickedDeferred()
{
	cout << "Button : Clicked! Deffered." << endl;
}

void example2::MouseClickedImmediate()
{
	cout << "Button : Clicked! Immediate." << endl;
}
