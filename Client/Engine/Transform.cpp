#include "pch.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: Super(name), _position(position), _rotation(rotation), _scale(scale)
{
	// CalculateModelMatrix();
}

Transform::~Transform()
{
}

void Transform::Init()
{
	// Set parent
	Super::Init();
	auto owner = GetOwner();
	if (owner)
	{
		if (auto parent = owner->GetParent())
			_parent = parent;
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

	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 rotMat = rotZ * rotY * rotX;

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), _position);

	return transMat * rotMat * scaleMat;
}

void Transform::UpdateModelMatrix()
{
	// ���� �� ���
	glm::mat4 localModel = CalculateLocalModel();

	// �θ� �ִٸ� �θ� ���� ���ؼ� ���� ���� �� ���
	if (auto parent = _parent.lock()) _model = parent->GetTransform()->GetModel() * localModel;
	else _model = localModel;

	_dirty = false;
}

void Transform::LateUpdate() { if (_dirty || !_parent.expired()) UpdateModelMatrix(); }