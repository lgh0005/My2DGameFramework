#include "pch.h"
#include "OptionButtonScript.h"
#include "UIBlocker.h"

OptionButtonScript::OptionButtonScript(const string& name) : Super(name)
{

}

void OptionButtonScript::Init()
{
#pragma region UI_Events
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
#pragma endregion

#pragma region UI_Setting

	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return;

	_settingUIObjectsName = 
	{
		"SettingUIPanel", "SettingUIText1", "SettingUIText2", "bgmToggle", "sfxToggle",
		"Check1", "Check2", "SettingClose", "Close", "SettingUI"
	};

	for (auto& name : _settingUIObjectsName) _settingUIObjects.push_back(scene->GetGameObject(name));

	shared_ptr<GameObject> go = scene->GetGameObject("UIBlocker");
	_uiBlockerComponent = static_pointer_cast<UIBlocker>(go->GetBehaviour("UIBlocker"));
	_uiBlockerComponent->SetCurrentScene(scene);
#pragma endregion
}

void OptionButtonScript::MouseHovered()
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

void OptionButtonScript::MouseExit()
{
	if (_uiBlockerComponent->IsInteractive())
	{
		_sfxPlayFlag = true;
		_button->SetTexture(RESOURCE.GetResource<Texture>("Button_Normal"));
	}
}

void OptionButtonScript::MouseClickedDeferred()
{
	cout << "Option Button : Clicked! Deffered." << endl;
	for (auto& obj : _settingUIObjects) { obj->SetActive(true); }
}

void OptionButtonScript::MouseClickedImmediate()
{
	cout << "Option Button : Clicked! Immediate." << endl;
	_uiBlockerComponent->SetInteractive(false);
}