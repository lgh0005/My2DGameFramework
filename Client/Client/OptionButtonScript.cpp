#include "pch.h"
#include "OptionButtonScript.h"

OptionButtonScript::OptionButtonScript(const string& name) : Super(name)
{

}

void OptionButtonScript::Init()
{
	auto self = GetSelf<OptionButtonScript>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	_button = static_pointer_cast<UIButton>(owner->GetRenderable("OptionButton"));

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

void OptionButtonScript::MouseHovered()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Select"));
}

void OptionButtonScript::MouseExit()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Normal"));
}

void OptionButtonScript::MouseClickedDeferred()
{
	cout << "Option Button : Clicked! Deffered." << endl;
}

void OptionButtonScript::MouseClickedImmediate()
{
	cout << "Option Button : Clicked! Immediate." << endl;
}