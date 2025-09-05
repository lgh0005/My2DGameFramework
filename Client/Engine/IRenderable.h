#pragma once
#include "IComponent.h"

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	// TODO : �ؽ��ĸ� �޾ƿͼ� OpenGL�� ���� ������ ���Ѿ� ��.
	IRenderable(const string& name);
	virtual ~IRenderable();

public:
	virtual void Render() abstract;
	virtual void Update() override;

protected:
	glm::mat4 _model = glm::mat4(1.0);
};

