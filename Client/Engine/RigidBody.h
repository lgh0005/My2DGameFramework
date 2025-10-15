#pragma once
#include "IComponent.h"

class RigidBody : public IComponent
{
	using Super = IComponent;

public:
	RigidBody(const string& name, float gravity, float velocity);
	virtual ~RigidBody() override = default;

public:
	virtual void Update() override;

public:
	void Jump(float force);
	void SetGroundY(float y) { _groundY = y; }
	void SetGravity(float g) { _gravity = g; }
	void ResetVelocity() { _velocity = 0.0f; }

	bool IsGrounded() const { return _isGrounded; }
	float GetVelocity() const { return _velocity; }

private:
	float _gravity = -9.8f;
	float _velocity = 0.0f;
	float _groundY = 0.0f;
	bool _isGrounded = true;

};

