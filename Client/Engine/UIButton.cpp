#include "pch.h"
#include "UIButton.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "ITexture.h"

UIButton::UIButton(const string& name, shared_ptr<Camera> camera, shared_ptr<ITexture> button, const glm::vec2& clickArea, Inputs::Mouse input)
	: Super(name, camera, button, clickArea), _input(input)
{

}

void UIButton::Update()
{
    Super::Update();

	auto MousePosition = INPUT.GetMousePosition(_camera);
	for (auto& binding : _eventBindings)
	{
		bool trigger = false;
		switch (binding.eventType)
		{
			case UI::UIEventType::OnHover: trigger = OnMouseHovered(MousePosition); break;
			case UI::UIEventType::OnExit: trigger = OnMouseExit(MousePosition); break;
			case UI::UIEventType::OnClick: trigger = OnMouseClick(MousePosition, _input); break;
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