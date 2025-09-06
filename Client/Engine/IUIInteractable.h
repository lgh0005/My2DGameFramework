#pragma once
#include "IUIElement.h"

class IUIInteractable : public IUIElement
{
	using Super = IUIElement;

public:
	IUIInteractable(const string& name, const glm::vec2& size);
	virtual ~IUIInteractable() override;

protected:
	bool IsMouseHovered(const glm::vec2& mousePos);
};

