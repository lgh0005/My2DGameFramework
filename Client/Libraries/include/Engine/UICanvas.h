#pragma once
#include "IUIElement.h"

class Camera;

class UICanvas : public IUIElement
{
	using Super = IUIElement;

public:
	UICanvas(const string& name, shared_ptr<Camera> camera, const glm::vec2& size);
	virtual ~UICanvas() override = default;

public:
	virtual void Init() override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;

public:
	void AddUIComponent(shared_ptr<IUIElement> ui);
	void RemoveUIComponent(shared_ptr<IUIElement> ui);

protected:
	vector<shared_ptr<IUIElement>> _uis;
};

