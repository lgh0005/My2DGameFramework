#pragma once
#include "IComponent.h"

class IRenderable : public IComponent
{
public:
	// TODO : �ؽ��ĸ� �޾ƿͼ� OpenGL�� ���� ������ ���Ѿ� ��.
	IRenderable(const string& name);
	virtual ~IRenderable();

public:
	virtual void Render() abstract;
};

