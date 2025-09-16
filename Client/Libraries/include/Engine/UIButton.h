#pragma once
#include "IUIRenderable.h"

class Camera;
class ITexture;

class UIButton : public IUIRenderable
{
	using Super = IUIRenderable;

public:
	UIButton(const string& name, 
			 shared_ptr<ITexture> button, shared_ptr<Shader> shader, shared_ptr<Camera> camera,
			 const glm::vec2& clickArea, Inputs::Mouse input);
	virtual ~UIButton() override;

public:
	virtual void Update() override;

public:
	void OnHoveredEvent(function<void()> event) { _hoverEvent = event; }
	void OnClickedEvent(function<void()> event) { _clickEvent = event; }
	void OnExitEvent(function<void()> event) { _exitEvent = event; }

private:
	shared_ptr<Camera> _camera;
	Inputs::Mouse _input;

	function<void()> _hoverEvent;
	function<void()> _clickEvent;
	function<void()> _exitEvent;
};

