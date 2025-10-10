#pragma once
#include "IUIRenderable.h"

class Camera;
class ITexture;

class UICheckBox : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UICheckBox(const string& name, const shared_ptr<Camera>& camera, shared_ptr<ITexture> texture, const glm::vec2& clieckArea, Inputs::Mouse input);
	virtual ~UICheckBox() override = default;

public:
	virtual void Update() override;

private:
	Inputs::Mouse _input;
};

