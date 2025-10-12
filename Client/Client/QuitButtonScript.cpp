#include "pch.h"
#include "QuitButtonScript.h"
#include "UIBlocker.h"

QuitButtonScript::QuitButtonScript(const string& name) : Super(name)
{

}

void QuitButtonScript::Init()
{
#pragma region UI_Event
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
#pragma endregion

#pragma region UI_Setting
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return;

	shared_ptr<GameObject> go = scene->GetGameObject("UIBlocker");
	_uiBlockerComponent = static_pointer_cast<UIBlocker>(go->GetBehaviour("UIBlocker"));
	_uiBlockerComponent->SetCurrentScene(scene);
#pragma endregion
}

void QuitButtonScript::MouseHovered()
{
	if (_uiBlockerComponent->IsInteractive())
	{
		if (_sfxPlayFlag)
		{
			AUDIO.PlaySFX("ButtonSFX");
			_sfxPlayFlag = false;
		}

		_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Select"));
	}
}

void QuitButtonScript::MouseExit()
{
	if (_uiBlockerComponent->IsInteractive())
	{
		_sfxPlayFlag = true;
		_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Normal"));
	}
}

void QuitButtonScript::MouseClickedDeferred()
{
	if (_uiBlockerComponent->IsInteractive())
	{
		GAME->Quit();
	}
}

void QuitButtonScript::MouseClickedImmediate()
{
	if (_uiBlockerComponent->IsInteractive())
	{
		AUDIO.PlaySFX("ButtonSFX");
	}
}