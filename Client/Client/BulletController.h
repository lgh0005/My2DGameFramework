#pragma once
#include "Engine\IBehaviour.h"
#include "Engine\IUniformProvider.h"

class BulletController : public IBehaviour, public IUniformProvider
{
	using Super = IBehaviour;

public:
	BulletController(const string& name);
	virtual ~BulletController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*=============================
//     Moving properties     //
//===========================*/
public:
	void SetDirection(EDirection dir) { _direction = dir; }
	virtual void ApplyUniforms(const shared_ptr<Shader>& shader) override;

private:
	void MoveBullet();

	shared_ptr<Shader> _bulletShader;
	shared_ptr<UniformSet> _bulletUniformSet;

	float _maxMoveDistance = 500.0f;
	float _minMoveDistance = -500.0f;

	float _speed = 900.0f;
	EDirection _direction = EDirection::Right;
	float _travelledDistance = 0.0f;

/*==============================
//     Collide properties     //
//============================*/
private:
	shared_ptr<BoxCollider> _bulletCollider;
	void OnCollisionWithEnemy(const shared_ptr<BoxCollider>& other);
};

