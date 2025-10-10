#pragma once
#include "Engine\IBehaviour.h"

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
	virtual void Update() override;

private:
	shared_ptr<Flipbook> _idleLeft;
	shared_ptr<Flipbook> _idleRight;
	shared_ptr<Flipbook> _walkLeft;
	shared_ptr<Flipbook> _walkRight;

	bool _isMoving = false;
	Direction _lastDir = Direction::Right;
	float _moveSpeed = 500.0f;
};

