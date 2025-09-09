#pragma once
#include "IUIElement.h"

class IUILayout : public IUIElement
{
	using Super = IUIElement;

public:
	IUILayout(const string& name, const glm::vec2& size);
	virtual ~IUILayout() override = default;

private:

};

