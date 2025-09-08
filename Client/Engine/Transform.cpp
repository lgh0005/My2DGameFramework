#include "pch.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: Super(name), _position(position), _rotation(rotation), _scale(scale)
{
	CalculateModelMatrix();
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModel()
{
	if (_dirty)
	{
		CalculateModelMatrix();

		// Model matrix update complete
		_dirty = false;
	}

	return _model;
}

void Transform::CalculateModelMatrix()
{
	// Scale
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), _scale);

	// Rotation (Euler angles, radians, ZYX 순)
	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), _rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), _rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 rotMat = rotZ * rotY * rotX;

	// Translation
	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), _position);

	// Model Matrix = Translation * Rotation * Scale
	_model = transMat * rotMat * scaleMat;
	
	// 부모 Transform 적용
	if (auto parent = _parent.lock())
		_model = parent->GetTransform()->GetModel() * _model;
}

