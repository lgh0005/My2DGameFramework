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

private:
	shared_ptr<Camera> _camera; // TODO : Camera는 상위 클래스의 멤버로 둘 필요가 있다.
	Inputs::Mouse _input;
};

