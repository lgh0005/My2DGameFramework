#include "pch.h"
#include "StartButtonScript.h"

StartButtonScript::StartButtonScript(const string& name) : Super(name)
{

}

void StartButtonScript::Init()
{
	auto self = GetSelf<StartButtonScript>();

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	_button = static_pointer_cast<UIButton>(owner->GetRenderable("StartButton"));

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

void StartButtonScript::MouseHovered()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Select"));
}

void StartButtonScript::MouseExit()
{
	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Normal"));
}

void StartButtonScript::MouseClickedDeferred()
{
	cout << "Start Button : Clicked! Deffered." << endl;
	// SCENE.LoadScene("DevScene");
}

void StartButtonScript::MouseClickedImmediate()
{
	cout << "Start Button : Clicked! Immediate." << endl;
}