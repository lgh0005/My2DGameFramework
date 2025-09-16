#include "pch.h"
#include "UIButton.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "ITexture.h"

UIButton::UIButton(const string& name, 
				   shared_ptr<ITexture> button, shared_ptr<Shader> shader, shared_ptr<Camera> camera, 
				   const glm::vec2& clickArea, Inputs::Mouse input)
	: Super(name, button, shader, clickArea), _camera(camera), _input(input)
{

}

UIButton::~UIButton()
{

}

void UIButton::Update()
{
    Super::Update();

	auto MousePosition = INPUT.GetMousePosition(_camera);
	if (_hoverEvent && OnHovered(MousePosition)) _hoverEvent();

	if (_exitEvent && OnExit(MousePosition)) _exitEvent();

	if (_clickEvent && OnClick(MousePosition, _input)) _clickEvent();
}