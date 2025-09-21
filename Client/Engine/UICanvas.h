#pragma once
#include "IUIContainer.h"

class UIGrid;

class UICanvas : public IUIContainer
{
	using Super = IUIContainer;

public:
	UICanvas(const string& name, const glm::vec2& size);
	virtual ~UICanvas() override = default;

public:
	virtual void Update() override;
};

