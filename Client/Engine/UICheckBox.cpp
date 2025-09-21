#include "pch.h"
#include "UICheckBox.h"

UICheckBox::UICheckBox(const string& name, shared_ptr<Camera> camera,
	shared_ptr<ITexture> texture, shared_ptr<Shader> shader,
	const glm::vec2& clieckArea, Inputs::Mouse input)
	: Super(name, camera, texture, shader, clieckArea), _input(input)
{

}

void UICheckBox::Update()
{
	Super::Update();

	auto MousePosition = INPUT.GetMousePosition(_camera);
	for (auto& binding : _eventBindings)
	{
		bool trigger = false;
		switch (binding.eventType)
		{
		case UI::UIEventType::OnToggle: trigger = OnToggled(MousePosition, _input); break;
		default: break;
		}

		if (trigger)
		{
			UIMANAGER.CreateEvent
			(
				binding.eventType, binding.eventPolicy,
				GetSelf<IUIElement>(),
				binding.mousePos, binding.mouseDelta,
				binding.callback
			);
		}
	}
}
