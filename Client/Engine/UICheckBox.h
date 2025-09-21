#pragma once
#include "IUIRenderable.h"

class Camera;
class ITexture;

class UICheckBox : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UICheckBox(const string& name, 
		shared_ptr<ITexture> texture, shared_ptr<Shader> shader, shared_ptr<Camera> camera,
		const glm::vec2& clieckArea, Inputs::Mouse input);
	virtual ~UICheckBox() override = default;

public:
	virtual void Update() override;

private:
	shared_ptr<Camera> _camera;
	Inputs::Mouse _input;
};

