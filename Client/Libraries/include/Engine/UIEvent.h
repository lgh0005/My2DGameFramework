#pragma once
#include "IUIElement.h"

struct UIEvent
{
	function<void()> callback;
	weak_ptr<IUIElement> sender;
	glm::vec2 mousePos;
	glm::vec2 mouseDelta;
	UI::UIEventType eventType;
	UI::UIEventPolicy eventPolicy;
};