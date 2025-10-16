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

glm::vec3 Transform::GetWorldPosition()
{
	glm::mat4 model = GetModel();
	return glm::vec3(model[3]);
}

glm::vec3 Transform::GetWorldScale()
{
	glm::mat4 model = GetModel();
	glm::vec3 scale;
	scale.x = glm::length(glm::vec3(model[0]));
	scale.y = glm::length(glm::vec3(model[1]));
	scale.z = glm::length(glm::vec3(model[2]));
	return scale;
}

glm::vec3 Transform::GetWorldRotation()
{
	glm::mat4 model = GetModel();

	// 모델 행렬에서 회전 행렬만 분리
	glm::mat3 rotationMat(model);

	// 회전을 Euler 각도로 변환 (pitch, yaw, roll)
	glm::vec3 scale = GetWorldScale();
	rotationMat[0] /= scale.x;
	rotationMat[1] /= scale.y;
	rotationMat[2] /= scale.z;

	glm::vec3 rotation;
	rotation.y = asin(-rotationMat[0][2]);
	if (cos(rotation.y) != 0.0f)
	{
		rotation.x = atan2(rotationMat[1][2], rotationMat[2][2]);
		rotation.z = atan2(rotationMat[0][1], rotationMat[0][0]);
	}
	else
	{
		rotation.x = atan2(-rotationMat[2][0], rotationMat[1][1]);
		rotation.z = 0;
	}
	return rotation;
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
	// 부모가 있으면 먼저 부모 갱신
	shared_ptr<Transform> parent;
	if (Utils::IsValidPtr<Transform>(_parent, parent))
	{
		//if (parent->_dirty)  // 부모가 더럽다면 먼저 갱신
		//	parent->UpdateModelMatrix();

		//// 로컬 모델 계산 후 부모 모델 곱하기
		_model = parent->GetModel() * CalculateLocalModel();
	}
	else
	{
		_model = CalculateLocalModel();
	}

	// 갱신 완료
	_dirty = false;
}

void Transform::LateUpdate() { if (_dirty || !_parent.expired()) UpdateModelMatrix(); }