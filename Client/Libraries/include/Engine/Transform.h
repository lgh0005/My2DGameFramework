#pragma once
#include "IComponent.h"

class GameObject;

class Transform : public IComponent
{
	using Super = IComponent;

public:
	Transform(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	virtual ~Transform() override = default;

public:
	virtual void Init() override;
	virtual void LateUpdate() override;

public:
	glm::mat4 GetModel();

public:
	void SetPosition(const glm::vec3& position) { _position = position; _dirty = true; }
	glm::vec3 GetPosition() { return _position; }
	void SetRotation(const glm::vec3& rotation) { _rotation = rotation; _dirty = true; }
	glm::vec3 GetRotation() { return _rotation; }
	void SetScale(const glm::vec3& scale) { _scale = scale; _dirty = true; }
	glm::vec3 GetScale() { return _scale; }

public:
	void UpdateModelMatrix();
	glm::vec3 GetWorldPosition();
	glm::vec3 GetWorldScale();
	glm::vec3 GetWorldRotation();

private:
	glm::mat4 CalculateLocalModel();

private:
	glm::mat4 _model;

	bool _dirty = true;
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _rotation = glm::vec3(0.0f);
	glm::vec3 _scale = glm::vec3(1.0f);

	weak_ptr<Transform> _parent;
};


