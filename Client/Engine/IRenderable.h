#pragma once
#include "IComponent.h"

class Camera;

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	IRenderable(const string& name);
	virtual ~IRenderable() override;

public:
	virtual void Render(const shared_ptr<Camera>& camera) abstract;
	virtual void Update() override;

protected:
	glm::mat4 _model = glm::mat4(1.0);
};

