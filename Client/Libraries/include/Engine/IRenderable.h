#pragma once
#include "IComponent.h"

class Camera;

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	IRenderable(const string& name, shared_ptr<Camera> camera);
	virtual ~IRenderable() override = default;

public:
	virtual void Render() abstract;
	virtual void Update() override;

protected:
	glm::mat4 _model = glm::mat4(1.0);
	shared_ptr<Camera> _camera;
};

