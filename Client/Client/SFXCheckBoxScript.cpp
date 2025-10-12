#include "pch.h"
#include "SFXCheckBoxScript.h"

SFXCheckBoxScript::SFXCheckBoxScript(const string& name) : Super(name)
{

}

void SFXCheckBoxScript::Init()
{
#pragma region UI_Events
	auto self = GetSelf<SFXCheckBoxScript>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	_checkBox = static_pointer_cast<UICheckBox>(owner->GetRenderable("sfxToggle"));
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

	_checkSprite = scene->GetGameObject("Check2");
#pragma endregion
}

void SFXCheckBoxScript::Update()
{
	bool toggled = _checkBox->IsToggled();
	_checkSprite->SetActive(!toggled);
}

void SFXCheckBoxScript::MouseToggle()
{
	bool toggled = _checkBox->IsToggled();
	if (toggled) AUDIO.SetVolume(AudioType::SFX, 0.0f);
	else AUDIO.SetVolume(AudioType::SFX, 1.0f);
}