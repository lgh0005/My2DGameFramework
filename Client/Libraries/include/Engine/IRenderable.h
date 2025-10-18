#pragma once
#include "IComponent.h"

class Shader;
class UniformSet;
class Camera;
class Transform;

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	IRenderable(const string& name);
	virtual ~IRenderable() override = default;

public:
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) abstract;
};

