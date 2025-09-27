#include "pch.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: Super(name), _position(position), _rotation(rotation), _scale(scale)
{
	
}

void Transform::Init()
{
	// Set parent
	Super::Init();

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(GetOwner(), owner))
	{
		shared_ptr<GameObject> parent;
		if (Utils::IsValidPtr<GameObject>(owner->GetParent(), parent))
			_parent = parent->GetTransform();
	}

	// Calculate model matrix
	UpdateModelMatrix();
}

glm::mat4 Transform::GetModel()
{
	if (_dirty) UpdateModelMatrix();
	return _model;
}

glm::mat4 Transform::CalculateLocalModel()
{
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), _scale);
	glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
	rotMat *= glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
	rotMat *= glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), _position);
	return transMat * rotMat * scaleMat;
}

void Transform::UpdateModelMatrix()
{
	// Calculate local model matrix
	glm::mat4 localModel = CalculateLocalModel();

	// If there is a parent, multiply its model to calculate the final world model
	shared_ptr<Transform> parent;
	if (Utils::IsValidPtr<Transform>(_parent, parent))
	{
		_model = parent->GetModel() * localModel;
	}
	else
	{
		_model = localModel;
	}

	// Set dirty
	_dirty = false;
}

void Transform::LateUpdate() { if (_dirty || !_parent.expired()) UpdateModelMatrix(); }