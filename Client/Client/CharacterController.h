#pragma once
#include "Engine\IBehaviour.h"

class BoxCollider;

class UniformSet;

enum class Direction
{
	Left,
	Right
};

class CharacterController : public IBehaviour
{
	using Super = IBehaviour;

public:
	CharacterController(const string& name);
	virtual ~CharacterController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

private:
	shared_ptr<BoxCollider> _collider;
	void OnCollisionEnter(const shared_ptr<BoxCollider>& other);

private:
	shared_ptr<Flipbook> _idleLeft;
	shared_ptr<Flipbook> _idleRight;
	shared_ptr<Flipbook> _walkLeft;
	shared_ptr<Flipbook> _walkRight;

	shared_ptr<Shader> _chararcterShader;
	shared_ptr< UniformSet> _characterUniformSet;

	bool _isMoving = false;
	Direction _lastDir = Direction::Right;
	float _moveSpeed = 500.0f;

	float _moveXRange = -200.0f;
};

