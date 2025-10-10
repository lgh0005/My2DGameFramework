#include "pch.h"
#include "QuitButtonScript.h"

QuitButtonScript::QuitButtonScript(const string& name) : Super(name)
{

}

void QuitButtonScript::Init()
{
	auto self = GetSelf<QuitButtonScript>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	_button = static_pointer_cast<UIButton>(owner->GetRenderable("QuitButton"));

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

void QuitButtonScript::MouseHovered()
{
	if (_sfxPlayFlag)
	{
		AUDIO.PlaySFX("ButtonSFX");
		_sfxPlayFlag = false;
	}

	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Select"));
}

void QuitButtonScript::MouseExit()
{
	_sfxPlayFlag = true;
	_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Normal"));
}

void QuitButtonScript::MouseClickedDeferred()
{
	GAME->Quit();
}

void QuitButtonScript::MouseClickedImmediate()
{
	AUDIO.PlaySFX("ButtonSFX");
}