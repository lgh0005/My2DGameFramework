#include "pch.h"
#include "BGMCheckBoxScript.h"

BGMCheckBoxScript::BGMCheckBoxScript(const string& name) : Super(name)
{

}

void BGMCheckBoxScript::Init()
{
#pragma region UI_Events
	auto self = GetSelf<BGMCheckBoxScript>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	_checkBox = static_pointer_cast<UICheckBox>(owner->GetRenderable("bgmToggle"));
	_checkBox->OnToggleEvent
	(
		[self]() { self->MouseToggle(); },
		UI::UIEventPolicy::Immediate,
		EMPTY_VEC2, EMPTY_VEC2
	);
#pragma endregion

#pragma region UI_Setting
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return;

	_checkSprite = scene->GetGameObject("Check1");
#pragma endregion
}

void BGMCheckBoxScript::Update()
{
	bool toggled = _checkBox->IsToggled();
	_checkSprite->SetActive(!toggled);
}

void BGMCheckBoxScript::MouseToggle()
{
	bool toggled = _checkBox->IsToggled();
	if (toggled) AUDIO.SetVolume(AudioType::BGM, 0.0f);
	else AUDIO.SetVolume(AudioType::BGM, 1.0f);
}