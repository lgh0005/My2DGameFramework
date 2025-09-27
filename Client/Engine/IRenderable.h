#pragma once
#include "IComponent.h"

class Shader;
class Camera;
class Transform;

class IRenderable : public IComponent
{
	using Super = IComponent;

public:
	IRenderable(const string& name);
	virtual ~IRenderable() override = default;

public:
	virtual void Init() override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) abstract;
	virtual void Update() override;

public:
	glm::mat4 GetModel() { return _model; }

protected:
	glm::mat4 _model = glm::mat4(1.0);
	shared_ptr<Transform> _ownerTransform;
};

