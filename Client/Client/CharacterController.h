#pragma once
#include "Engine\IBehaviour.h"

class BoxCollider;
class UniformSet;
class FlipbookPlayer;

class CharacterController : public IBehaviour
{
	using Super = IBehaviour;

public:
	CharacterController(const string& name);
	virtual ~CharacterController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*=============================
//     Moving properties     //
=============================*/
private:
	shared_ptr<Shader> _chararcterShader;
	shared_ptr< UniformSet> _characterUniformSet;

	shared_ptr<FlipbookPlayer> _CharacterFlipbookPlayer;
	shared_ptr<Flipbook> _idleRight;
	shared_ptr<Flipbook> _walkRight;

	shared_ptr<Transform> _ownerTransform;
	bool _isMoving = false;
	EDirection _lastDir = EDirection::Right;
	float _moveSpeed = 500.0f;

/*=================
//     Misc.     //
=================*/
private:
	float _maxMoveXRange = -200.0f;
	float _minMoveXRange = -400.0f;
};

