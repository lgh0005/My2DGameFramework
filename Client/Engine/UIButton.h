#pragma once
#include "IUIRenderable.h"

class Camera;
class ITexture;

class UIButton : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UIButton(const string& name, shared_ptr<Camera> camera, shared_ptr<ITexture> button, const glm::vec2& clickArea, Inputs::Mouse input);
	virtual ~UIButton() override = default;

public:
	virtual void Awake(const shared_ptr<GameObject>& owner) override;
	virtual void Update() override;

private:
	Inputs::Mouse _input;
};