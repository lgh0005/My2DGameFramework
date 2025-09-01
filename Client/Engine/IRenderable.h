#pragma once
#include "IComponent.h"

class IRenderable : public IComponent
{
public:
	// TODO : 텍스쳐를 받아와서 OpenGL을 통해 렌더링 시켜야 함.
	IRenderable(const string& name);
	virtual ~IRenderable();

public:
	virtual void Render() abstract;
};

