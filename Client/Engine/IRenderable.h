#pragma once
#include "IComponent.h"

class Camera;

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	// TODO : �ؽ��ĸ� �޾ƿͼ� OpenGL�� ���� ������ ���Ѿ� ��.
	IRenderable(const string& name);
	virtual ~IRenderable();

public:
	virtual void Render(const shared_ptr<Camera>& camera) abstract;
	virtual void Update() override;

protected:
	glm::mat4 _model = glm::mat4(1.0);
};

