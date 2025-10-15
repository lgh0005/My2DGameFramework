#pragma once
#include "Engine\IBehaviour.h"

class BulletController : public IBehaviour
{
	using Super = IBehaviour;

public:
	BulletController(const string& name);
	virtual ~BulletController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*==============================
//     Collide properties     //
//============================*/
private:
	shared_ptr<BoxCollider> _bulletCollider;
	void OnCollideWithEnemy(const shared_ptr<BoxCollider>& other);

/*=============================
//     Moving properties     //
//===========================*/
public:
	void SetDirection(Direction dir) { _direction = dir; }

private:
	void MoveBullet();

	shared_ptr<Shader> _bulletShader;
	shared_ptr<UniformSet> _bulletUniformSet;

	float _maxMoveDistance = 500.0f;
	float _minMoveDistance = -500.0f;

	float _speed = 600.0f;
	Direction _direction = Direction::Right;
	float _travelledDistance = 0.0f;
};

