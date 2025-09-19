#pragma once
#include "IUIElement.h"

class IUIContainer : public IUIElement
{
	using Super = IUIElement;

public:
	IUIContainer(const string& name, const glm::vec2& size);
	virtual ~IUIContainer() override = default;

public:
	virtual void Init() override;
	virtual void Render(const shared_ptr<Camera>& camera) override;

public:
	void AddUIComponent(shared_ptr<IUIElement> ui);
	void RemoveUIComponent(shared_ptr<IUIElement> ui);

protected:
	vector<shared_ptr<IUIElement>> _uis;
};

