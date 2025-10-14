#pragma once
#include "Engine\IBehaviour.h"

class BoxCollider;
class UniformSet;
class FlipbookPlayer;

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

/*=============================
//    Collider properties    //
=============================*/
private:
	shared_ptr<BoxCollider> _collider;
	void OnCollisionEnter(const shared_ptr<BoxCollider>& other);

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
	Direction _lastDir = Direction::Right;
	float _moveSpeed = 500.0f;

/*=================
//     Misc.     //
=================*/
private:
	float _moveXRange = -200.0f;
};

