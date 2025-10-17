#include "pch.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"

RigidBody::RigidBody(const string& name, float gravity, float velocity) 
	: Super(name), _gravity(gravity), _velocity(velocity)
{

}

void RigidBody::Update()
{
	Super::Update();

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	auto transform = owner->GetTransform();
	glm::vec3 pos = transform->GetPosition();

	if (!_isGrounded)
	{
		pos.y += _velocity * TIME.deltaTime;
		_velocity += _gravity * TIME.deltaTime;

		// 땅보다 아래로 내려가면 멈추기
		if (pos.y <= _groundY)
		{
			pos.y = _groundY;
			_velocity = 0.0f;
			_isGrounded = true;
		}
	}

	transform->SetPosition(pos);
}

void RigidBody::Jump(float force)
{
	if (_isGrounded)
	{
		_velocity = force;
		_isGrounded = false;
	}
}
